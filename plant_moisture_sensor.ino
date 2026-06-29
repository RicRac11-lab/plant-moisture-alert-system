#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "AdafruitIO_WiFi.h"

/************************ CONFIGURATION *******************************/
#define IO_USERNAME  "IO_USERNAME"
#define IO_KEY       "IO_KEY"

#define WIFI_SSID    "WIFI_SSID"
#define WIFI_PASS    "WIFI_PASS"
/**********************************************************************/

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// TWO SEPARATE FEEDS: One for graphics, one for text triggers
AdafruitIO_Feed *moistureFeed = io.feed("soil-moisture");
AdafruitIO_Feed *alertFeed    = io.feed("plant-alerts");

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

const int moisturePin = 34; // Connect AOUT of the moisture sensor to GPIO 34
const int DRY_VALUE = DRY_VALUE; // Put in the benchmarked dry raw value (mine is 2500, yours might be different)
const int WET_VALUE = WET_VALUE;  // Put in the benchmarked wet raw value (mine is 735, yours might be different)

unsigned long lastUploadTime = 0;
const unsigned long uploadInterval = 10000; 

unsigned long lastAlertTime = 0;
const unsigned long alertCooldown = 21600000; // 6 hours
const int CRITICAL_DRY_THRESHOLD = 15; 

void setup() {
  Serial.begin(115200);
  u8g2.begin();
  
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 30, "Connecting to WiFi...");
  u8g2.sendBuffer();

  io.connect();
  while(io.status() < AIO_CONNECTED) { delay(500); }
}

void loop() {
  io.run();

  int rawValue = analogRead(moisturePin);
  int moisturePercent = map(rawValue, DRY_VALUE, WET_VALUE, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);
  
  // Update local display (Always works!)
  u8g2.clearBuffer();         
  u8g2.setFont(u8g2_font_ncenB08_tr); 
  u8g2.drawStr(0, 12, "--- PLANT MONITOR ---");
  u8g2.drawStr(0, 35, "Raw Value:");
  u8g2.setCursor(80, 35); u8g2.print(rawValue);
  u8g2.drawStr(0, 55, "Moisture:");
  u8g2.setCursor(80, 55); u8g2.print(moisturePercent); u8g2.print("%");
  u8g2.sendBuffer();          
  
  // Cloud Logic
  if (millis() - lastUploadTime >= uploadInterval) {
    lastUploadTime = millis();
    
    // Always send the clean percentage to your visual gauge feed
    moistureFeed->save(moisturePercent);
    Serial.print("Streaming to Gauge: "); Serial.print(moisturePercent); Serial.println("%");
    
    // IF dry and cooldown is clear, shoot the alert flag to the ALERT feed instead!
    if (moisturePercent <= CRITICAL_DRY_THRESHOLD && (millis() - lastAlertTime >= alertCooldown || lastAlertTime == 0)) {
      lastAlertTime = millis();
      
      alertFeed->save(-99); 
      Serial.println("!!! Threshold breached! Alert flag sent to plant-alerts feed !!!");
    }
  }

  delay(100);
}