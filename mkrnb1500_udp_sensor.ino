#include <MKRNB.h>
#include <ArduinoLowPower.h>

NB netzZugang;
NBUDP udpSocket;

const int sensorPin = A0;                        // Analogeingang für Sensor
const unsigned long sendeIntervallMs = 3600000;  // 60 Minuten (in ms)
const char* zielIp = "udp.os.1nce.com";          // Ziel-IP im 1NCE NAT-Backbone
const int zielPort = 4445;                       // Ziel-Port im Backend
const char* apn = "iot.1nce.net";                // APN für 1NCE

unsigned long zeitLetzteSendung = 0;             // Zeitpunkt der letzten Sendung

// Hilfsfunktion: Verbindung aufbauen
bool verbindeNetz() {
  Serial.print("Stelle Mobilfunkverbindung her (APN: ");
  Serial.print(apn);
  Serial.print(") ... ");

  if (netzZugang.begin(apn) != NB_READY) {
    Serial.println("Fehler!");
    return false;
  }

  Serial.println("OK, Mobilfunk verbunden.");
  return true;
}

void setup() {
  Serial.begin(9600);
  while (!Serial); // Warten auf Serial Monitor

  Serial.println("NB-IoT UDP-Sensor startet...");

  // Erste Netzverbindung versuchen
  while (!verbindeNetz()) {
    Serial.println("Neuer Versuch in 30 Sekunden...");
    delay(30000);
  }

  udpSocket.begin(zielPort);

  // Sofort beim ersten loop() senden
  zeitLetzteSendung = millis() - sendeIntervallMs;
}

void loop() {
  // Prüfen, ob es Zeit für eine Sendung ist
  if (millis() - zeitLetzteSendung >= sendeIntervallMs) {
    int sensorsignal = analogRead(sensorPin);
    uint8_t messwertByte = sensorsignal / 4;

    Serial.print("Sende Sensorwert: ");
    Serial.print(messwertByte);
    Serial.print(" (ADC: ");
    Serial.print(sensorsignal);
    Serial.println(") über UDP...");

    // UDP-Paket senden
    if (!udpSocket.beginPacket(zielIp, zielPort)) {
      Serial.println("Fehler beim Öffnen des UDP-Pakets. Versuche Reconnect...");
      if (!verbindeNetz()) {
        Serial.println("Netz nicht verfügbar – überspringe diesen Zyklus.");
        return; // Nicht senden, nächster Versuch im nächsten Zyklus
      }
    }

    udpSocket.write(&messwertByte, 1);
    if (udpSocket.endPacket() == 1) {
      Serial.println("UDP-Versand erfolgreich.");
    } else {
      Serial.println("UDP-Versand fehlgeschlagen!");
    }

    // Zeitstempel für nächste Sendung merken
    zeitLetzteSendung = millis();

    // ⚡ Strom sparen: für das Intervall in Sleep gehen
    Serial.println("Gehe in Sleep-Modus...");
    LowPower.sleep(sendeIntervallMs);
    Serial.println("Aufgewacht.");
  }

  delay(200); // kleine Entlastung
}
