#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// =====================================================
// AQUADRIP - WOKWI DEMO MODE
// Demonstrates NORMAL, LOW and CRITICAL states
// =====================================================

// LEDs
#define GREEN_LED 18
#define BLUE_LED  19
#define RED_LED   16

// Buzzer
#define BUZZER 25

// LCD
#define SDA_PIN 21
#define SCL_PIN 22

LiquidCrystal_I2C lcd(0x27, 16, 2);

// =====================================================
// SETUP
// =====================================================

void setup()
{
  Serial.begin(115200);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  Wire.begin(SDA_PIN, SCL_PIN);

  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AQUADRIP");
  lcd.setCursor(0, 1);
  lcd.print("DEMO MODE");

  delay(2000);
}

// =====================================================
// NORMAL STATE
// =====================================================

void normalState()
{
  float level = 100.0;
  float volume = 500.0;

  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Level: ");
  lcd.print(level, 0);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("NORMAL ");
  lcd.print(volume, 0);
  lcd.print("ml");

  Serial.println("NORMAL - 100% - 500ml");
}

// =====================================================
// LOW STATE
// =====================================================

void lowState()
{
  float level = 20.0;
  float volume = 100.0;

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Level: ");
  lcd.print(level, 0);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("LOW ");
  lcd.print(volume, 0);
  lcd.print("ml");

  Serial.println("LOW - 20% - 100ml");
}

// =====================================================
// CRITICAL STATE
// =====================================================

void criticalState()
{
  float level = 5.0;
  float volume = 25.0;

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, HIGH);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Level: ");
  lcd.print(level, 0);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("!! CRITICAL !!");

  Serial.println("CRITICAL - 5% - 25ml");

  // Buzzer for 10 seconds
  unsigned long startTime = millis();

  while (millis() - startTime < 10000)
  {
    digitalWrite(BUZZER, HIGH);
    delay(500);

    digitalWrite(BUZZER, LOW);
    delay(500);
  }
}

// =====================================================
// LOOP
// =====================================================

void loop()
{
  // ---------------- NORMAL ----------------
  normalState();
  delay(10000);

  // ---------------- LOW ----------------
  lowState();
  delay(10000);

  // ---------------- CRITICAL ----------------
  criticalState();

  // Repeat
}