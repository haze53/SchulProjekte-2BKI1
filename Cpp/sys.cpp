#include <WiFi.h>
#include <HTTPClient.h>
#include <BluetoothSerial.h>
 
const char* ssid = "WLAN_NAME";
const char* password = "WLAN_PASSWORT";
 
const char* serverUrl = "Server URL";

BluetoothSerial SerialBT;
 
// buttonPins werden nicht mehr verwendet, da Bluetooth genutzt wird
// int buttonPins[8] = {13, 12, 14, 27, 26, 25, 33, 32};
int ledPins[8] = {2, 4, 16, 17, 5, 18, 19, 21};
int resetButtonPin = 15;
int nextButtonPin = 23;
int trueButtonPin = 22;
int falseButtonPin = 34;
 
int pressOrder[8];
int pressedCount = 0;
int currentIndex = -1;
bool gameStarted = false;
 
// Timing-Variablen für Button-Entprellung
unsigned long lastButtonPress = 0;
unsigned long lastModeratorPress = 0;
const unsigned long debounceDelay = 300;  // 300ms zwischen Button-Drücken
const unsigned long moderatorDebounce = 500;  // 500ms für Moderator-Buttons
 
void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Buzzer_System"); // Bluetooth mit Name initialisieren
  Serial.println("Bluetooth gestartet. Name: ESP32_Buzzer_System");
 
  WiFi.begin(ssid, password);
  Serial.print("Verbinde mit WLAN");
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nVerbunden mit WLAN!");
 
  for (int i = 0; i < 8; i++) {
    // buttonPins werden nicht mehr initialisiert (Bluetooth)
    // pinMode(buttonPins[i], INPUT_PULLUP);
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
    pressOrder[i] = -1;
  }
 
  pinMode(resetButtonPin, INPUT_PULLUP);
  pinMode(nextButtonPin, INPUT_PULLUP);
  pinMode(trueButtonPin, INPUT_PULLUP);
  pinMode(falseButtonPin, INPUT_PULLUP);
}
 
void loop() {
  unsigned long currentTime = millis();
 
  // Reset-Button mit verbesserter Entprellung
  if (digitalRead(resetButtonPin) == LOW &&
      (currentTime - lastModeratorPress > moderatorDebounce)) {
    sendData("0R");
    resetGame();
    lastModeratorPress = currentTime;
    delay(300);
  }
 
 
  // True-Button mit verbesserter Entprellung
  if (digitalRead(trueButtonPin) == LOW &&
      (currentTime - lastModeratorPress > moderatorDebounce)) {
    if (!gameStarted && pressedCount > 0) {
      sendData("Start");
      gameStarted = true;
      Serial.println("Spiel gestartet");
 
      for (int i = 0; i < 8; i++) {
        digitalWrite(ledPins[i], LOW);
      }
    } else if (gameStarted && currentIndex != -1) {
      sendData(String(currentIndex + 1) + "T");
      nextQuestion();
    }
    lastModeratorPress = currentTime;
    delay(300);
  }
 
 
  // Next-Button mit verbesserter Entprellung
  if (digitalRead(nextButtonPin) == LOW &&
      (currentTime - lastModeratorPress > moderatorDebounce)) {
    sendData("0N");
    nextQuestion();
    lastModeratorPress = currentTime;
    delay(300);
  }
 
  // False-Button mit verbesserter Entprellung
  if (digitalRead(falseButtonPin) == LOW && gameStarted && currentIndex != -1 &&
      (currentTime - lastModeratorPress > moderatorDebounce)) {
    sendData(String(currentIndex + 1) + "F");  
    moveToNext();
    lastModeratorPress = currentTime;
    delay(300);
  }
 
  // Spieler-Buzzer über Bluetooth mit verbesserter Entprellung und Moderator-Schutz
  if (SerialBT.available() &&
      (currentTime - lastButtonPress > debounceDelay) &&
      (currentTime - lastModeratorPress > moderatorDebounce)) {
    char received = SerialBT.read();
    // Erwarte Zeichen '1' bis '8' für Spieler 1-8
    if (received >= '1' && received <= '8') {
      int i = received - '1'; // Konvertiere '1'-'8' zu Index 0-7
      
      if (pressOrder[i] == -1) {
        pressOrder[i] = pressedCount;
        pressedCount++;
        sendData(String(i + 1) + "A");  
       
        digitalWrite(ledPins[i], HIGH);
 
        if (currentIndex == -1) {
          currentIndex = i;
        }
       
        lastButtonPress = currentTime;
        delay(300);  // Längere Pause für bessere Entprellung
      }
    }
  }
}
 
void resetGame() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(ledPins[i], LOW);
    pressOrder[i] = -1;
  }
  pressedCount = 0;
  currentIndex = -1;
  gameStarted = false;
}
 
void nextQuestion() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(ledPins[i], LOW);
    pressOrder[i] = -1;
  }
  pressedCount = 0;
  currentIndex = -1;
}
 
void moveToNext() {
  if (currentIndex != -1) {
    digitalWrite(ledPins[currentIndex], LOW);
  }
 
  int nextIndex = -1;
  int smallestOrder = 9999;
 
  for (int i = 0; i < 8; i++) {
    if (pressOrder[i] > pressOrder[currentIndex] && pressOrder[i] < smallestOrder) {
      nextIndex = i;
      smallestOrder = pressOrder[i];
    }
  }
 
  if (nextIndex != -1) {
    currentIndex = nextIndex;
    digitalWrite(ledPins[currentIndex], HIGH);
  } else {
    currentIndex = -1;
  }
}
 
void sendData(String message) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");
 
    String jsonData = "{\"message\": \"" + message + "\"}";
    int httpResponseCode = http.POST(jsonData);
 
    if (httpResponseCode > 0) {
      Serial.println("Daten gesendet: " + message);
      Serial.println("Antwort: " + http.getString());
    } else {
      Serial.println("Fehler beim Senden der Daten");
    }
 
    http.end();
  } else {
    Serial.println("Keine Verbindung zum WiFi");
  }
}