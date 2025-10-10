# Arduino-Datenübertragung aus abgelegenen Gebieten per IoT-SIM-Karte

Dieses Repository enthält ein Arduino-Projekt zur Datenübertragung aus abgelegenen Gebieten mithilfe einer IoT-SIM-Karte und dem Arduino MKR NB 1500.

## Einleitung

In Zeiten der Digitalisierung gibt es immer mehr Anwendungsfälle, in denen Sensordaten aus abgelegenen Gebieten ohne WLAN- oder Mobilfunkabdeckung übertragen werden müssen. Eine elegante Lösung bietet hier die Nutzung des NarrowBand-IoT (NB-IoT) Standards mit speziellen IoT-SIM-Karten.

Dieses Projekt zeigt, wie man mit dem Arduino MKR NB 1500 und einer IoT-SIM-Karte Sensordaten energieeffizient über das Mobilfunknetz übertragen kann.

![Arduino MKR NB 1500 Setup](https://prilchen.de/wp-content/uploads/2022/11/image-2.png)

## Überblick

Das Projekt nutzt folgende Komponenten:

* **Arduino MKR NB 1500** - Das zentrale Board mit integriertem NB-IoT/LTE-M Modul
* **IoT-SIM-Karte** - Speziell für IoT-Anwendungen optimierte SIM-Karte mit günstigen Datentarifen
* **Kapazitiver Sensor** - Beispielhafter Sensor zur Datenerfassung

### Funktionsweise

Der Arduino MKR NB 1500 nutzt das NB-IoT-Netzwerk zur Datenübertragung. NB-IoT ist ein schmalbandiger Funkstandard, der speziell für IoT-Anwendungen entwickelt wurde und sich durch:

- Hohe Reichweite und Gebäudedurchdringung
- Geringen Energieverbrauch
- Niedrige Kosten
- Unterstützung einer großen Anzahl von Geräten

auszeichnet.

### Benötigte Libraries

Für das Projekt werden folgende Arduino-Libraries benötigt:

* [MKRNB-Library (MKRNB.h)](https://docs.arduino.cc/libraries/mkrnb/) - Für die Kommunikation mit dem NB-IoT-Modul
* [ArduinoLowPower-Library](https://github.com/arduino-libraries/ArduinoLowPower) - Für energiesparende Sleep-Modi
* [RTCZero-Library (RTCZero.h)](https://docs.arduino.cc/libraries/rtczero/) - Für zeitgesteuerte Aufwachvorgänge

## Hardware-Komponenten

| Komponente | Link |
|------------|------|
| Arduino MKR NB 1500 | [berrybase.de](https://www.berrybase.de/arduino-nb-1500) |
| Kapazitiver Sensor | [Amazon](https://amzn.to/42zRvBJ) |

## Sketch

Der vollständige Arduino-Sketch befindet sich in der Datei `mkrnb1500_udp_sensor.ino`.

## Lizenz

Dieses Projekt steht unter der MIT-Lizenz.
