#include <LiquidCrystal.h>

// Pin configuration
const int soilMoisturePin = A0;   // Analog pin for soil moisture sensor
const int pumpPin = 8;            // Digital pin for the relay module
const int buzzerPin = 9;          // Digital pin for buzzer (optional)
const int lcdRS = 7, lcdEN = 6, lcdD4 = 5, lcdD5 = 4, lcdD6 = 3, lcdD7 = 2;

// Moisture level thresholds
const int moistureThreshold = 400;  // Threshold value (0-1023) to turn on the pump

// Timing variables
unsigned long lastWateringTime = 0;
const unsigned long wateringInterval = 10000; // 10 seconds for demo purposes

// Initialize the LCD library
LiquidCrystal lcd(lcdRS, lcdEN, lcdD4, lcdD5, lcdD6, lcdD7);

void setup() {
  // Set pin modes
  pinMode(soilMoisturePin, INPUT);
  pinMode(pumpPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("Watering System");

  // Start with the pump turned off
  digitalWrite(pumpPin, LOW);
  digitalWrite(buzzerPin, LOW);

  delay(2000);
}

void loop() {
  // Read the soil moisture value
  int moistureValue = analogRead(soilMoisturePin);
  lcd.clear();
  lcd.print("Moisture: ");
  lcd.print(moistureValue);

  // Check if the soil is dry
  if (moistureValue > moistureThreshold && millis() - lastWateringTime > wateringInterval) {
    // Turn on the pump
    digitalWrite(pumpPin, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Watering...");
    delay(5000);  // Pump stays on for 5 seconds (adjust as needed)

    // Turn off the pump
    digitalWrite(pumpPin, LOW);
    lastWateringTime = millis();

    // Optional: Trigger a buzzer to indicate watering is done
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
  } else {
    lcd.setCursor(0, 1);
    lcd.print("No Water Needed");
  }

  // Delay for a short while before taking the next reading
  delay(2000);
}

// Function to check if it's time to water
bool isTimeToWater(unsigned long interval) {
  return millis() - lastWateringTime > interval;
}

// Function to trigger buzzer
void triggerBuzzer(int duration) {
  digitalWrite(buzzerPin, HIGH);
  delay(duration);
  digitalWrite(buzzerPin, LOW);
}

// Function to handle LCD updates
void updateLCD(int moistureValue, bool isWatering) {
  lcd.clear();
  lcd.print("Moisture: ");
  lcd.print(moistureValue);

  if (isWatering) {
    lcd.setCursor(0, 1);
    lcd.print("Watering...");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("No Water Needed");
  }
}
