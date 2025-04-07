#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// Pins für Neopixel 7 Segmentanzeige
#define LED_PIN    8 // Anschlusspin des Neopixel-LED-Streifens
#define NUM_LEDS   56 // Anzahl der LEDs
#define BRIGHTNESS 255 // Helligkeit (0-255)
#define NUM_DIGITS   4  // Anzahl der Stellen

// Pin für die Lichtschranken
#define START_GATE_PIN 4
#define END_GATE_PIN 6

//Pin für Piezo
#define PIEZO_PIN 7

//Pin für Reset
#define RESET_PIN 9

//Pin für Testmode
//#define Operating_Mode_PIN_1 12
#define Operating_Mode_PIN_1 2
#define Operating_Mode_PIN_2 3
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

// Variable, um den aktuellen Zustand des Operating_Mode Schalters zu speichern
int Operating_Mode = HIGH;
int Operating_Mode_Alt = HIGH;
int Operating_Response = 0;
int Operating_Mode_PIN_1_Status = 0;
int Operating_Mode_PIN_2_Status = 0;

// Start- und Stop-Zeit
unsigned long startTime = 0;
unsigned long stopTime = 0;

const uint8_t digits[10][7] = {
  {1, 1, 1, 0, 1, 1, 1}, // 0
  {1, 0, 0, 0, 1, 0, 0}, // 1
  {1, 1, 0, 1, 0, 1, 1}, // 2
  {1, 1, 0, 1, 1, 1, 0}, // 3
  {1, 0, 1, 1, 1, 0, 0}, // 4
  {0, 1, 1, 1, 1, 1, 0}, // 5
  {0, 1, 1, 1, 1, 1, 1}, // 6
  {1, 1, 0, 0, 1, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 1, 1, 0}  // 9
};

void displayDigit(int digit, int digitPosition) {
  if (digit >= 0 && digit <= 9 && digitPosition >= 0 && digitPosition < NUM_DIGITS) {
    int startIndex = digitPosition * 14; // Jetzt 14 LEDs pro Digit (7 Segmente * 2 LEDs)
    
    for (int i = 0; i < 7; i++) {
      int ledIndex1 = startIndex + (i * 2);
      int ledIndex2 = ledIndex1 + 1;
      if (digits[digit][i] == 1) {
        strip.setPixelColor(ledIndex1, BRIGHTNESS, 0, 0);
        strip.setPixelColor(ledIndex2, BRIGHTNESS, 0, 0);
      } else {
        strip.setPixelColor(ledIndex1, 0, 0, 0);
        strip.setPixelColor(ledIndex2, 0, 0, 0);
      }
    }
  }
}

void displayNumber(int number) {
  if (number >= 0 && number < 10000) {
    int thousandsDigit = (number / 1000) % 10;
    int hundredsDigit = (number / 100) % 10;
    int tensDigit = (number / 10) % 10;
    int onesDigit = number % 10;
    
    displayDigit(thousandsDigit, 3);
    displayDigit(hundredsDigit, 2);
    displayDigit(tensDigit, 1);
    displayDigit(onesDigit, 0);
    
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

void Ein_Lichtschranken_Mode(){
  //Lichtschranke Start
  if ( ((Start_State == LOW && previous_Start_State == HIGH) || (END_State == LOW && previous_END_State == HIGH )) && timerRunning == LOW) {
    startTimer();
    previous_Start_State = LOW;
    previous_END_State = LOW;
    Serial.println("Start");
    digitalWrite(PIEZO_PIN, HIGH);
    delay(100);
  }

  //Lichtschranke Start zurücksetzen
  if (Start_State == HIGH && previous_Start_State == LOW) {
    Serial.println("Start/Stop");
    previous_Start_State = HIGH;
    digitalWrite(PIEZO_PIN, LOW);
    delay(200);
  }

  //Lichtschranke Stop
  if (((Start_State == LOW && previous_Start_State == HIGH) || (END_State == LOW && previous_END_State == HIGH )) && timerRunning == HIGH) {
    stopTimer();
    previous_END_State = LOW;
    previous_Start_State = LOW;
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
  // Reset Taster gedrückt ==> Timer auf 0 zurücksetzen
  if(Reset_State == LOW) {
    resetTimer();
  }

 // Anzeigen der aktuellen Zeit auf dem Display
 if (timerRunning) {
   // Aktuelle Zeit abrufen
   unsigned long currentTime = millis();

   // Anzeige der vergangenen Zeit
   displayMillis(currentTime - startTime);
  }
}

void Zwei_Lichtschranken_Mode(){
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
  
  // Reset Taster gedrückt ==> Timer auf 0 zurücksetzen
  if(Reset_State == LOW) {
    resetTimer();
  }

 // Anzeigen der aktuellen Zeit auf dem Display
 if (timerRunning) {
   // Aktuelle Zeit abrufen
   unsigned long currentTime = millis();

   // Anzeige der vergangenen Zeit
   displayMillis(currentTime - startTime);
  }
}

void Test_Mode(){
  timerRunning = false;

  Serial.print("TestMode: ");
  digitalWrite(Testmode_LED, HIGH);

  if (Start_State == HIGH) {
    Operating_Response = 1000;
  } else {
    Operating_Response = 0;
  }

  if (END_State == HIGH) {
    Operating_Response = Operating_Response + 1;
  }

  displayNumber(Operating_Response);
  Serial.println(Operating_Response);
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
  pinMode(Operating_Mode_PIN_1, INPUT_PULLUP);
  pinMode(Operating_Mode_PIN_2, INPUT_PULLUP);
  pinMode(Testmode_LED, OUTPUT);
  digitalWrite(Testmode_LED, LOW);

  //Starten der Seriellen Schnittstelle
  Serial.begin(9600);

  // Konfiguration für Neopixel 7 Segmentanzeige
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.setPixelColor(28, BRIGHTNESS, BRIGHTNESS, BRIGHTNESS);
  strip.show(); //
  displayNumber(0);
}

void loop() {
  // Lesen des Tasterzustands
  Start_State = digitalRead(START_GATE_PIN);
  END_State = digitalRead(END_GATE_PIN);
  Reset_State = digitalRead(RESET_PIN);
  //Operating_Mode = !digitalRead(Operating_Mode_PIN_1);

  Operating_Mode_PIN_1_Status = !digitalRead(Operating_Mode_PIN_1);
  Operating_Mode_PIN_2_Status= !digitalRead(Operating_Mode_PIN_2);

  if (Operating_Mode_PIN_1_Status == 0 && Operating_Mode_PIN_2_Status == 1){ //Ein_Lichtschranken_Mode
    Operating_Mode = 0;
  }else if (Operating_Mode_PIN_1_Status == 1 && Operating_Mode_PIN_2_Status == 0){ //Zwei_Lichtschranken_Mode
    Operating_Mode = 1;
  }else { //Testmode
    Operating_Mode = 2;
  }

  if (Operating_Mode != Operating_Mode_Alt){
    Operating_Mode_Alt = Operating_Mode;
    displayNumber(0);
    digitalWrite(PIEZO_PIN, LOW);
  }

  if (Operating_Mode == 0 && Operating_Response != 0) {
    Operating_Response = 0;
    digitalWrite(Testmode_LED, LOW);
    stopTimer();
  }

  switch (Operating_Mode){
    case 0:
      Ein_Lichtschranken_Mode();
      Serial.println("EIN");
    break;

    case 1:
      Zwei_Lichtschranken_Mode();
      Serial.println("Zwei");
    break;

    case 2:
      Test_Mode();
    break;

    default:
      Serial.println("Error: TestmodeSwitch, false reading");
    break;
  }
  
}
