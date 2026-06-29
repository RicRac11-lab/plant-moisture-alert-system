# Plant Moisture Alert System

## Description
This is a project that programs the ESP-32 microcontroller to read moisture levels from the soil moisture sensor, then displays the raw value and percentage on the OLED display. To send emails to yourself, a dashboard and feeds are set up on Adafruit IO, then an applet is set up on IFTTT to connect to the feeds from Adafruit IO. 

## Parts
1. ESP-32 Microcontroller (https://www.amazon.co.uk/dp/B0D8T5XD3P?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1)
2. Capacitive Analog Soil Moisture Sensor Module (https://www.amazon.co.uk/dp/B0BTHL6M19?ref=ppx_yo2ov_dt_b_fed_asin_title)
3. I2C SH1106 or SSD1306 1.3-inch or 0.96-inch OLED display (https://www.amazon.co.uk/dp/B0DFCH21S2?ref=ppx_yo2ov_dt_b_fed_asin_title)
4. Breadboard
5. Jumper wires

## Step 1: Benchmarking the dry and wet values
**Pin connection (Moisture Sensor -> ESP32)**
- VCC -> 3V3 
- GND -> GND
- AOUT -> GPIO 34

**Calibration Instructions:**
1. Upload the benchmarking.ino code to the ESP32.
2. Open the Serial Monitor in Arduino IDE (the magnifying glass icon in the top-right corner, or by going to Tools > Serial Monitor)
3. Set the "Baud rate dropdown" in the bottom right of the Serial Monitor to 115200 baud.
4. Leave the sensor dry and write down the dry value (e.g. 2500)
5. Dip the sensor into a glass of water and write down the wet value (e.g. 735)
---
## Step 2: Setting Up the Email Notification
### In Arduino IDE:
1. In  Arduino IDE, go to Tools > Manage Libraries.
2. Search for Adafruit IO Arduino.
3. Click Install

### In Adafruit IO
1. Go to io.adafruit.com and create a free account.
2. Go to Feeds and create a new feed named "soil-moisture"
3. Go to Dashboards and create a dashboard named "Plant Monitor".
4. Add a Gauge block or a Line Chart block to your dashboard and link it to your "soil-moisture" feed.
5. Go to Feeds and create a new feed named "plant-alerts"
6. Copy your Adafruit IO Username and Active Key. **You will need these for your code!!**

### Connect Adafruit IO to IFTTT
1. On the IFTTT website or app, click Create to start a new "Applet".
2. Click If This (Add).
3. Search for Adafruit IO and select it.
4. Choose the trigger called "Monitor a feed on Adafruit IO".
5. It will prompt you to log into your Adafruit IO account once to authorise the connection.
6. Select: 
- Feed: plant-alerts.
- Relationship: "equal to".
- Value: -99

### Set Up the Email Notification Action
1. Click Then That (Add) in IFTTT.
2. Search for "Email".
3. Select "Send me an email"
4. Customise your alert email subject and body text.
---
## Step 3: The Final Iteration
### Pin Connection: 
Follow the Circuit Diagram

**OLED Display to ESP32:**
- **GND** -> GND
- **VCC** -> 3V3
- **SCL** -> GPIO 22
- **SDA** -> GPIO 21

**Moisture Sensor to ESP32:**
- **VCC** -> 3V3
- **GND** -> GND
- **AOUT** -> GPIO 34

### Software Configuration
Open `plant_moisture_sensor.ino` and make the following configurations before uploading:
- Insert your Adafruit IO username into line 7 (`IO_USERNAME`).
- Insert your Adafruit IO Active Key into line 8 (`IO_KEY`).
- Insert your local home Wi-Fi Network Name (SSID) into line 10 (`WIFI_SSID`).
- Insert your Wi-Fi password into line 11 (`WIFI_PASS`).
- Insert your custom benchmarked dry value into line 23 (`DRY_VALUE`).
- Insert your custom benchmarked wet value into line 24 (`WET_VALUE`).

### Display Optimisation:
- **If you are using an SH1106 display:** Leave line 20 exactly as it is.
- **If you are using an SSD1306 display:** Comment out line 20 and replace it with: 
  `U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);`
