#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); 

const int laserPin = 7;
const int sensorPin = A0;

// ==========================================
// DATA SMOOTHING VARIABLES
// ==========================================
const int numReadings = 10;
int readings[numReadings];      
int readIndex = 0;              
long total = 0;                  
int average = 0;                

void setup() {
  Serial.begin(9600);
  
  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, HIGH); // Turn laser ON
  
  lcd.init();                      
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Data Gathering Mode");
  lcd.setCursor(0, 1);
  lcd.print("Warming up sensor...");
  
  // Initialize all smoothing readings to 0
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read the raw data from the sensor
  int rawValue = analogRead(sensorPin);

  // ==========================================
  // MOVING AVERAGE ALGORITHM
  // ==========================================
  total = total - readings[readIndex];         // Subtract the last reading
  readings[readIndex] = rawValue;              // Read from the sensor
  total = total + readings[readIndex];         // Add the reading to the total
  readIndex = readIndex + 1;                   // Advance to the next position

  if (readIndex >= numReadings) {              // If we're at the end of the array...
    readIndex = 0;                             // ...wrap around to the beginning
  }
  
  average = total / numReadings;               // Calculate the stable average

  // ==========================================
  // DISPLAY DATA
  // ==========================================
  // 1. To the LCD Screen
  lcd.setCursor(0, 0);
  lcd.print("Raw Data: ");
  lcd.print(rawValue);
  lcd.print("    "); 

  lcd.setCursor(0, 1);
  lcd.print("Stable:   ");
  lcd.print(average);
  lcd.print("    "); 

  // 2. To the Serial Plotter/Monitor (Tools > Serial Plotter)
  Serial.print("Raw:");
  Serial.print(rawValue);
  Serial.print(",");
  Serial.print("Stable:");
  Serial.println(average);

  delay(100); 
}