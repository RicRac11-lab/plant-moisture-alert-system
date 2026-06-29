// Define the pin connected to AOUT
const int moisturePin = 34; // Connect the AOUT of the moisture sensor to pin 34 of the ESP-32

void setup() {
  Serial.begin(115200); // Start the serial communication at 115200 baud
}

void loop() {
  int rawValue = analogRead(moisturePin);  // Read the analog value (0 to 4095)
  
  Serial.print("Raw Moisture Value: "); // Print the raw value to the Serial Monitor
  Serial.println(rawValue);
  
  delay(1000); // Wait 1 second before reading again
}