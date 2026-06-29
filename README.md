# Plant Moisture Alert System

**Parts**
1. ESP-32 Microcontroller (https://www.amazon.co.uk/dp/B0D8T5XD3P?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1)
2. Capacitive Analog Soil Moisture Sensor Module (https://www.amazon.co.uk/dp/B0BTHL6M19?ref=ppx_yo2ov_dt_b_fed_asin_title)
3. I2C SSH1106 or SSD1306 1.3 inch or 0.96 inch OLED display (https://www.amazon.co.uk/dp/B0DFCH21S2?ref=ppx_yo2ov_dt_b_fed_asin_title)
4. Breadboard
5. Jumper wires

**Description**
<br> This is a project that programs the ESP-32 microcontroller to read moisture levels from the soil moisture sensor, then displays the raw value and percentage on the OLED display. To send emails to yourself, a dashboard and feeds are set up on Adafruit IO, then an applet is set up on IFTTT to connect to the feeds from Adafruit IO. 

**Notes on Code**
