#include <Arduino.h>
#include <TM1637Display.h>

// Pins für die 7-Segment-Anzeige
#define CLK_PIN 2
#define DIO_PIN 3
// Pin für den Taster
#define BUTTON_PIN 4
//Pin für Piezo
#define PIEZO_PIN 5

// Initialisierung des Display-Objekts
TM1637Display display(CLK_PIN, DIO_PIN);

// Variable, um den aktuellen Zustand des Timers zu speichern (gestartet oder gestoppt)
bool timerRunning = false;
bool buttonState= HIGH;
bool previousButtonState = HIGH;

// Start- und Stop-Zeit
unsigned long startTime = 0;
unsigned long stopTime = 0;

void setup() {
  // Initialisierung des Displays
  display.setBrightness(0x0a);  // Helligkeit einstellen (0x00 bis 0x0f)
  display.showNumberDecEx(0, 0b01000000, true);

  // Konfiguration des Taster-Pins
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Konfiguration des Piezo-Pins
  pinMode(PIEZO_PIN, OUTPUT);

  //Starten der Seriellen Schnittstelle
  Serial.begin(9600);
}

// Funktion zum Starten des Timers
void startTimer() {
  // Timer starten und Startzeit festlegen
  startTime = millis();
  timerRunning = true;
}

// Funktion zum Stoppen des Timers
void stopTimer() {
  // Timer stoppen und Stopzeit festlegen
  stopTime = millis();
  timerRunning = false;
}

// Funktion zur Anzeige der Zeit in Millisekunden auf dem Display
void displayMillis(unsigned long milliseconds) {
  display.showNumberDecEx(milliseconds/10, 0b01000000, true);
}

void loop() {
  // Lesen des Tasterzustands
  buttonState = digitalRead(BUTTON_PIN);

//Taster Starten
  if (buttonState == LOW && previousButtonState == HIGH && timerRunning == LOW) {
    startTimer();
    previousButtonState = LOW;
    Serial.println("Start");
    digitalWrite(PIEZO_PIN, HIGH);
    delay(50);
  }

//Taster Stop
  if (buttonState == LOW && previousButtonState == HIGH && timerRunning == HIGH) {
    stopTimer();
    previousButtonState = LOW;
    Serial.println("Stop");
    digitalWrite(PIEZO_PIN, HIGH);
    delay(50);
  }

//Taster zurücksetzen
  if (buttonState == HIGH && previousButtonState == LOW) {
    Serial.println("Start/Stop");
    previousButtonState = HIGH;
    digitalWrite(PIEZO_PIN, LOW);
    delay(50);
  }

  // Überprüfen, ob der Timer läuft
  if (timerRunning) {
    // Aktuelle Zeit abrufen
    unsigned long currentTime = millis();

    // Anzeige der vergangenen Zeit
    displayMillis(currentTime - startTime);
  }
  
}