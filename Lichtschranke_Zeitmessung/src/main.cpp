#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// Pins für Neopixel 7 Segmentanzeige
#define LED_PIN    8 // Anschlusspin des Neopixel-LED-Streifens
#define NUM_LEDS   29 // Anzahl der LEDs pro Digit
#define BRIGHTNESS 255 // Helligkeit (0-255)
#define NUM_DIGITS   4  // Anzahl der Stellen
// Pins für die 7-Segment-Anzeige
#define CLK_PIN 2
#define DIO_PIN 3
// Pin für die Lichtschranken
#define START_GATE_PIN 4
#define END_GATE_PIN 6
//Pin für Piezo
#define PIEZO_PIN 5
//Pin für Reset
#define RESET_PIN 9
//Pin für Testmode
#define Testmode_PIN 12
#define Testmode_LED 13

// Initialisierung des Neopixel-LED-Streifens
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Variable, um den aktuellen Zustand des Timers zu speichern (gestartet oder gestoppt)
bool timerRunning = false;

// Variable, um den aktuellen Zustand der Lichtschranken zu speichern
bool Start_State= HIGH;
bool previous_Start_State = HIGH;
bool END_State= HIGH;
bool previous_END_State = HIGH;

// Variable, um den aktuellen Zustand des Resettasters zu speichern
bool Reset_State = HIGH;

// Variable, um den aktuellen Zustand des Testmode Schalters zu speichern
int Operating_Mode = HIGH;
int Operating_Response = 0;

// Start- und Stop-Zeit
unsigned long startTime = 0;
unsigned long stopTime = 0;

const uint16_t segments[] = {
  0b1110111, // 0
  0b0100100, // 1
  0b1101011, // 2
  0b1101101, // 3
  0b0111100, // 4
  0b1011101, // 5
  0b1011111, // 6
  0b1100100, // 7
  0b1111111, // 8
  0b1111101  // 9
};

void displayDigit(int digit, int digitPosition) {
  if (digit >= 0 && digit <= 9 && digitPosition >= 0 && digitPosition < NUM_DIGITS) {
    uint16_t segmentMask = segments[digit];
    int startIndex = digitPosition * 7; // Berechne den Startindex für die LED des angegebenen Digits
    
    for (int i = 0; i < 7; i++) {
      if (bitRead(segmentMask, i) == 1) {
        strip.setPixelColor(startIndex + i, 255, 255, 255); // Setze die LED auf Rot (An)
      } else {
        strip.setPixelColor(startIndex + i, 0, 0, 0); // Setze die LED auf Schwarz (Aus)
      }
    }
  }
}

void displayNumber(int number) {
  if (number >= 0 && number < 10000) {
    int hundredsDigit = (number / 1000) % 10;
    int tenthsDigit = (number / 100) % 10;
    int onesDigit = (number / 10) % 10;
    int tensDigit = number % 10;


    displayDigit(hundredsDigit, 3); // Anzeige der Hundertstelstelle
    displayDigit(tenthsDigit, 2); // Anzeige der Zehntelstelle
    displayDigit(onesDigit, 1); // Anzeige der Einerstelle
    displayDigit(tensDigit, 0); // Anzeige der Zehnerstelle
    
    strip.show();
  }
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
  displayNumber(milliseconds/10);
}

// Funktion zum Zurücksetzen des Timers
void resetTimer() {
  stopTimer();
  displayNumber(0);
}

void setup() {
  // Konfiguration der Lichtschranken-Pins
  pinMode(START_GATE_PIN, INPUT_PULLUP);
  pinMode(END_GATE_PIN, INPUT_PULLUP);

  // Konfiguration des Piezo-Pins
  pinMode(PIEZO_PIN, OUTPUT);
  digitalWrite(PIEZO_PIN, LOW);

  // Konfiguration des Reset-Pins
  pinMode(RESET_PIN, INPUT_PULLUP);

  // Konfiguration des Testmode-Pins und der Testmode LED
  pinMode(Testmode_PIN, INPUT_PULLUP);
  pinMode(Testmode_LED, OUTPUT);
  digitalWrite(Testmode_LED, LOW);

  //Starten der Seriellen Schnittstelle
  Serial.begin(9600);

  // Konfiguration für Neopixel 7 Segmentanzeige
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.setPixelColor(28, 255, 255, 255);
  strip.show(); //
  displayNumber(0);
}

void loop() {
  // Lesen des Tasterzustands
  Start_State = digitalRead(START_GATE_PIN);
  END_State = digitalRead(END_GATE_PIN);
  Reset_State = digitalRead(RESET_PIN);
  Operating_Mode = !digitalRead(Testmode_PIN);

  if (Operating_Mode == 0 && Operating_Response != 0) {
    Operating_Response = 0;
    digitalWrite(Testmode_LED, LOW);
    stopTimer();
  }

  switch (Operating_Mode){
    case 0: // Normalmodus
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
    break;

    case 1:
      Serial.print("TestMode: ");
      timerRunning = false;
      digitalWrite(Testmode_LED, HIGH);
      if (Start_State == HIGH) {
        Operating_Response = 1000;
      } else {
        Operating_Response = 0;
      }

      if (END_State == HIGH) {
        Operating_Response = Operating_Response + 1;
      }

      //display.showNumberDecEx(Operating_Response, 0b01000000, true);
      Serial.println(Operating_Response);

    break;

    default:
      Serial.println("Error: TestmodeSwitch, false reading");
    break;
  }
  
}
