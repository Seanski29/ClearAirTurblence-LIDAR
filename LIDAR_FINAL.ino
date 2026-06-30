#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD (Address 0x27, 20 columns, 4 rows)
LiquidCrystal_I2C lcd(0x27, 20, 4); 

// Pin Definitions
const int laserPin = 7;
const int sensorPin = A0;

// ==========================================
// --- ADJUSTABLE THRESHOLD RANGES ---
// ==========================================
// Change these numbers based on your fog testing
int normalLimit = 150; // 0 to 150
int lightLimit = 350;     //151 to 350
int moderateLimit = 500;   // 351 to 500
int maxReading = 1000;     // Maximum expected severe reading

// ==========================================
// DATA SMOOTHING (Moving Average Filter)
// ==========================================
const int numReadings = 15; 
int readings[numReadings];      
int readIndex = 0;              
long total = 0;                  
int average = 0;                

void setup() {
  Serial.begin(9600);
  
  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, HIGH); 
  
  lcd.init();                      
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("NAAP LIDAR Dashboard");
  lcd.setCursor(0, 1);
  lcd.print("Booting Interface...");
  
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
  
  delay(2000); 
  lcd.clear();
}

void loop() {
  // 1. Read and Smooth the Data
  int rawValue = analogRead(sensorPin);

  total = total - readings[readIndex];         
  readings[readIndex] = rawValue;              
  total = total + readings[readIndex];         
  readIndex = readIndex + 1;                   

  if (readIndex >= numReadings) {              
    readIndex = 0;                             
  }
  average = total / numReadings;               

  // ==========================================
  // ROW 0: The Header (20 chars exactly)
  // ==========================================
  lcd.setCursor(0, 0);
  lcd.print("  LIDAR TURBULENCE  ");

  // ==========================================
  // ROW 1: Atmospheric Reading 
  // ==========================================
  lcd.setCursor(0, 1);
  lcd.print("Weather Reading: ");
  lcd.print(average);
  lcd.print("   "); // Blank spaces clear leftover digits

  // ==========================================
  // ROW 2: The Volume Slider UI
  // ==========================================
  // Map the average reading (0 - maxReading) to a 20-character width
  int fillLevel = map(average, 0, maxReading, 0, 20);
  // Ensure the bar doesn't break if numbers spike past 1000
  fillLevel = constrain(fillLevel, 0, 20); 

  lcd.setCursor(0, 2);
   if (average <= normalLimit) {
    lcd.print("TURBULENCE: NORMAL  ");
  } 
  else if (average <= lightLimit) {
    lcd.print("TURBULENCE: LIGHT          ");
  } 
    else if (average <= moderateLimit) {
    lcd.print("TURBULENCE: MODERATE  ");
  } 
  else {
    lcd.print("TURBULENCE: SEVERE  ");
  }
  // ==========================================
  // ROW 3: The Turbulence Status Text
  // ==========================================
  lcd.setCursor(0, 3);
   for (int i = 0; i < 20; i++) {
    // Keep the static dividers at specific positions
    if (i == 6) {
      lcd.print("");
    } 
    else if (i == 10) {
      lcd.print("");
    } 
     else if (i == 20) {
      lcd.print("");
    } 
    // Fill the bar with a block character if the reading reaches this point
    else if (i < fillLevel) {
      lcd.write(255); // Character 255 creates a solid black square on most I2C LCDs!
    } 
    // Leave blank space if empty
    else {
      lcd.print(" ");
    }
  }
  
 

  // 10Hz Refresh Rate to keep the LCD and processor perfectly stable
  delay(100); 
}