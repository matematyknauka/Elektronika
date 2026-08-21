#include <WiFi.h>
#include <time.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  // Czekanie na połączenie
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nPolaczono!");
  configTime(3600, 3600, "pool.ntp.org");

  // Pobranie czasu w setup
  struct tm timeinfo;
  // Czekamy chwilę na synchronizację czasu z serwerem
  while (!getLocalTime(&timeinfo)) {
    delay(100);
  }
  
  // Wypisanie czasu tylko raz
  Serial.printf("Godzina pobrana w setup: %02d:%02d:%02d\n", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
  Serial.print(String("Dodatkowo") + timeinfo.tm_hour);
}

void loop() {
  // Pusta pętla - nie potrzebujemy nic więcej
}
