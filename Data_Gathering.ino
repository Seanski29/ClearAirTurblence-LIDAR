// ==========================================
// KNN DATA GATHERING TOOL
// ==========================================
// CHANGE THIS WORD BEFORE EVERY TEST: 
// Options: "NORMAL", "LIGHT", "MODERATE", "SEVERE"
String currentScenario = "NORMAL"; 

const int laserPin = 7;
const int sensorPin = A0;

void setup() {
  // Set baud rate to 9600 for Serial Monitor
  Serial.begin(9600);
  
  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, HIGH); 
  
  // Give the user 5 seconds to open the Serial Monitor
  delay(5000);
  Serial.println("Dataset_Label,Raw_Value");
}

void loop() {
  int rawValue = analogRead(sensorPin);

  // Print in a perfect CSV format (Comma Separated Values)
  Serial.print(currentScenario);
  Serial.print(",");
  Serial.println(rawValue);

  // Take exactly 1 reading per second
  delay(1000); 
}
