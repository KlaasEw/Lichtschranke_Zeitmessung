#include <Arduino.h>
#include <TM1637Display.h>

// Pins für die 7-Segment-Anzeige
#define CLK_PIN 2
#define DIO_PIN 3
// Pin für die Lichtschranken
#define START_GATE_PIN 4
#define END_GATE_PIN 6
//Pin für Piezo
#define PIEZO_PIN 5
//Pin für Reset
#define RESET_PIN 7

// Initialisierung des Display-Objekts
TM1637Display display(CLK_PIN, DIO_PIN);

// Variable, um den aktuellen Zustand des Timers zu speichern (gestartet oder gestoppt)
bool timerRunning = false;
bool Start_State= HIGH;
bool previous_Start_State = HIGH;
bool END_State= HIGH;
bool previous_END_State = HIGH;
bool Reset_State = HIGH;

// Start- und Stop-Zeit
unsigned long startTime = 0;
unsigned long stopTime = 0;

void setup() {
  // Initialisierung des Displays
  display.setBrightness(0x0a);  // Helligkeit einstellen (0x00 bis 0x0f)
  display.showNumberDecEx(0, 0b01000000, true);

  // Konfiguration der Lichtschranken-Pins
  pinMode(START_GATE_PIN, INPUT_PULLUP);
  pinMode(END_GATE_PIN, INPUT_PULLUP);

  // Konfiguration des Piezo-Pins
  pinMode(PIEZO_PIN, OUTPUT);

  // Konfiguration des Reset-Pins
  pinMode(RESET_PIN, INPUT_PULLUP);

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

// Funktion zum Zurücksetzen des Timers
void resetTimer() {
  stopTimer();
  display.showNumberDecEx(0, 0b01000000, true);
}

void loop() {
  // Lesen des Tasterzustands
  Start_State = digitalRead(START_GATE_PIN);
  END_State = digitalRead(END_GATE_PIN);
  Reset_State = digitalRead(RESET_PIN);


//Lichtschranke Start
  if (Start_State == LOW && previous_Start_State == HIGH && timerRunning == LOW) {
    startTimer();
    previous_Start_State = LOW;
    Serial.println("Start");
    digitalWrite(PIEZO_PIN, HIGH);
    delay(50);
  }

//Lichtschranke Start zurücksetzen
  if (Start_State == HIGH && previous_Start_State == LOW) {
    Serial.println("Start/Stop");
    previous_Start_State = HIGH;
    digitalWrite(PIEZO_PIN, LOW);
    delay(50);
  }

//Lichtschranke Stop
  if (END_State == LOW && previous_END_State == HIGH && timerRunning == HIGH) {
    stopTimer();
    previous_END_State = LOW;
    Serial.println("Stop");
    digitalWrite(PIEZO_PIN, HIGH);
    delay(50);
  }

//Lichtschranke Start zurücksetzen
  if (END_State == HIGH && previous_END_State == LOW) {
    Serial.println("Start/Stop");
    previous_END_State = HIGH;
    digitalWrite(PIEZO_PIN, LOW);
    delay(50);
  }

//Timer auf 0 zurücksetzen
  if(Reset_State == LOW) {
    resetTimer();
  }

  // Überprüfen, ob der Timer läuft
  if (timerRunning) {
    // Aktuelle Zeit abrufen
    unsigned long currentTime = millis();

    // Anzeige der vergangenen Zeit
    displayMillis(currentTime - startTime);
  }
  
}