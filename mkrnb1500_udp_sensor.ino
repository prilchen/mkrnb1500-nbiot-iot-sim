#include <MKRNB.h>
#include "ArduinoLowPower.h"
#include <RTCZero.h>

// PIN-Nummer (SIM Karte)
const char PINNUMBER[] = "";

// APN Data (IoT.1nce.net)
const char GPRS_APN[] = "iot.1nce.net";
const char GPRS_LOGIN[] = "";
const char GPRS_PASSWORD[] = "";

// Empfänger (IP-Adresse des Rechners)
const char server[] = "192.168.178.xx";
const int port = 9999;

// NB-IoT Objekte
NB nbAccess;
GPRS gprsAccess;
NBUDP udpClient;
RTCZero rtc;

// Variablen
int sensorValue = 0;
int status = NB_ERROR;
unsigned long lastSendTime = 0;
const unsigned long sendInterval = 60000; // 60 Sekunden

void setup() {
  // Serielle Kommunikation starten
  Serial.begin(9600);
  while (!Serial) {
    ; // Warten auf serielle Verbindung
  }

  Serial.println("Starting NB-IoT connection...");

  // Verbindung zum NB-IoT-Netzwerk herstellen
  while (status != NB_READY) {
    Serial.println("Attempting NB-IoT network connection");
    status = nbAccess.begin(PINNUMBER);

    if (status != NB_READY) {
      Serial.println("Connection failed. Retrying...");
      delay(1000);
    } else {
      Serial.println("Connected to NB-IoT network");
    }
  }

  // GPRS-Verbindung herstellen
  Serial.println("Attaching to GPRS...");
  if (gprsAccess.attachGPRS(GPRS_APN, GPRS_LOGIN, GPRS_PASSWORD) == GPRS_READY) {
    Serial.println("GPRS attached");
  } else {
    Serial.println("GPRS connection failed");
    while (true);
  }

  // RTC initialisieren
  rtc.begin();
}

void loop() {
  unsigned long currentTime = millis();

  // Daten senden alle 60 Sekunden
  if (currentTime - lastSendTime >= sendInterval) {
    lastSendTime = currentTime;

    // Sensor auslesen (Beispiel: analoger Eingang A0)
    sensorValue = analogRead(A0);

    Serial.print("Sensor Value: ");
    Serial.println(sensorValue);

    // UDP-Paket senden
    udpClient.beginPacket(server, port);
    udpClient.print("Sensor: ");
    udpClient.print(sensorValue);
    udpClient.endPacket();

    Serial.println("Data sent via UDP");
  }

  // Deep Sleep für Energieeinsparung (optional)
  // LowPower.sleep(50000); // 50 Sekunden Sleep
}
