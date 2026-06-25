#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h>

// ---------------- LCD ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------- RFID ----------------
#define SS_PIN 4
#define RST_PIN 2
MFRC522 rfid(SS_PIN, RST_PIN);

// ---------------- Pins ----------------
#define TRIG_PIN 5
#define ECHO_PIN 17
#define IR_PIN 27

#define RED_LED 32
#define GREEN_LED 25
#define BLUE_LED 26

#define SERVO_PIN 13

Servo gateServo;

// ---------------- UID ----------------
byte owner1[] = {0xA3, 0xF6, 0x52, 0x36};
byte owner2[] = {0x41, 0x99, 0xAE, 0x7B};

byte admin1[] = {0x4B, 0xE2, 0xFD, 0x72};
byte admin2[] = {0xAA, 0xA9, 0xBD, 0x7A};

byte member1[] = {0xEB, 0xF6, 0x70, 0x71};
byte member2[] = {0x8B, 0xCD, 0xD0, 0x72};

// ---------------- STATE ----------------
enum State {
  IDLE,
  VISITOR_DETECTED,
  SCAN_CARD,
  GRANTED,
  DENIED
};

State state = IDLE;
State lastState = IDLE;

// ---------------- LCD ----------------
void showLCD(String l1, String l2 = "") {
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");

  lcd.setCursor(0, 0);
  lcd.print(l1);

  lcd.setCursor(0, 1);
  lcd.print(l2);
}

// ---------------- LED ----------------
void setLED(int r, int g, int b) {
  digitalWrite(RED_LED, r);
  digitalWrite(GREEN_LED, g);
  digitalWrite(BLUE_LED, b);
}

// ---------------- DISTANCE (0–50 cm filter) ----------------
float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) return -1;

  float distance = duration * 0.034 / 2;

  if (distance > 50) return -1;

  return distance;
}

// ---------------- UID MATCH ----------------
bool matchUID(byte *a, byte *b) {
  for (byte i = 0; i < 4; i++) {
    if (a[i] != b[i]) return false;
  }
  return true;
}

String checkCard(byte *uid) {

  if (matchUID(uid, owner1) || matchUID(uid, owner2)) return "OWNER";

  if (matchUID(uid, admin1) || matchUID(uid, admin2)) return "ADMIN";

  if (matchUID(uid, member1) || matchUID(uid, member2)) return "MEMBER";

  return "DENIED";
}

// ---------------- GATE ANIMATION ----------------
void openGateAnimated() {

  setLED(0, 0, 1);
  showLCD("Gate Opening", "Please wait");

  // opening animation
  for (int pos = 0; pos <= 90; pos += 2) {
    gateServo.write(pos);
    delay(20);
  }

  showLCD("Access Granted", "Welcome!");
  setLED(0, 1, 0);
  delay(2000);

  showLCD("Closing Gate", "");

  // closing animation
  for (int pos = 90; pos >= 0; pos -= 2) {
    gateServo.write(pos);
    delay(20);
  }
}

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();

  SPI.begin();
  rfid.PCD_Init();

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IR_PIN, INPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  gateServo.attach(SERVO_PIN);
  gateServo.write(0);

  showLCD("Waking up", "Initializing...");
  setLED(0, 0, 1);
  delay(2000);

  showLCD("System ready");
  setLED(0, 1, 0);

}

// ---------------- LOOP ----------------
void loop() {

  float dist = getDistance();
  bool irDetected = digitalRead(IR_PIN);

  // -------- STATE UPDATE DISPLAY --------
  if (state != lastState) {
    lastState = state;

    if (state == IDLE) {
      showLCD("System Ready");
      setLED(0, 1, 0);
    }

    else if (state == VISITOR_DETECTED) {
      showLCD("Visitor Detected");
      setLED(0, 1, 0);
    }

    else if (state == SCAN_CARD) {
      showLCD("Scan Your Card");
      setLED(1, 0, 0);
    }

    else if (state == DENIED) {
      showLCD("Access Denied");
      setLED(0, 0, 1);
    }
  }

  // -------- LOGIC --------
  if (state == IDLE) {
    if (dist > 0 && dist <= 30) {
      state = VISITOR_DETECTED;
    }
  }

  else if (state == VISITOR_DETECTED) {
    if (irDetected == LOW) {
      state = SCAN_CARD;
    }
  }

  else if (state == SCAN_CARD) {

    if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
      return;
    }

    String role = checkCard(rfid.uid.uidByte);

    if (role == "OWNER") {
      showLCD("Hello Cutie!", "Welcome Home");
      state = GRANTED;
    }
    else if (role == "ADMIN") {
      showLCD("Admin Access", "Granted");
      state = GRANTED;
    }
    else if (role == "MEMBER") {
      showLCD("Member Access", "Granted");
      state = GRANTED;
    }
    else {
      state = DENIED;
    }

    delay(1000);
  }

  else if (state == GRANTED) {
    openGateAnimated();
    state = IDLE;
  }

  else if (state == DENIED) {
    delay(1500);
    state = IDLE;
  }
}