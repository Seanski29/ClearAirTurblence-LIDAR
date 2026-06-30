#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD
LiquidCrystal_I2C lcd(0x27, 20, 4); 

// Pin
const int laserPin = 7;
const int sensorPin = A0;

// ==========================================
// DATA SMOOTHING (Moving Average Filter)
// ==========================================
// fixed-size array. Allocates memory once on boot.
const int numReadings = 15; 
int readings[numReadings];      
int readIndex = 0;              
long total = 0;                  
int average = 0;                

void setup() {
  // Start Serial for computer logging/plotter
  Serial.begin(9600);
  
  // Power up the Laser
  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, HIGH); 
  
  // Boot up LCD
  lcd.init();                      
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("NAAP Data Logger");
  lcd.setCursor(0, 1);
  lcd.print("System Warming Up...");
  
  // Smoothing array with 0s to prevent math errors
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
  
  delay(2000); // Let the sensor stabilize
  lcd.clear();
}

void loop() {
  // 1. Read the raw backscatter data
  int rawValue = analogRead(sensorPin);

  // 2. Perform the Moving Average Math
  total = total - readings[readIndex];         // Subtract the oldest reading
  readings[readIndex] = rawValue;              // Insert the new reading
  total = total + readings[readIndex];         // Add to total
  readIndex = readIndex + 1;                   // Move to the next index

  // Wrap around the array when it hits the end
  if (readIndex >= numReadings) {              
    readIndex = 0;                             
  }
  
  // Calculate the stable smoothed number
  average = total / numReadings;               

  // ==========================================
  // SAFE LCD DISPLAY (Zero String Objects)
  // ==========================================
  
  // Display Raw Data
  lcd.setCursor(0, 0);
  lcd.print("Raw:    ");
  lcd.print(rawValue);
  lcd.print("    "); // Blank spaces overwrite leftover digits from previous loops

  // Display Stable Data
  lcd.setCursor(0, 1);
  lcd.print("Stable: ");
  lcd.print(average);
  lcd.print("    "); // Blank spaces overwrite leftover digits

  // ==========================================
  // SERIAL OUTPUT (For Arduino Serial Plotter)
  // ==========================================
  // If you open Tools > Serial Plotter, you will see a live graph of these two lines!
  Serial.print("Raw:");
  Serial.print(rawValue);
  Serial.print(",Stable:");
  Serial.println(average);

  // 10Hz Refresh Rate. Keeps the I2C bus stable and prevents freezing.
  delay(100); 
}