#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <SPI.h>
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h> 

Adafruit_BMP280 bmp; 
float temperature; 
float Altitude; 
float pressure;
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

#define OLED_MOSI 11 
#define OLED_CLK 13
#define OLED_DC 9 
#define OLED_CS 10 
#define OLED_RST 8 

Adafruit_SSD1306 display(
  SCREEN_WIDTH, 
  SCREEN_HEIGHT,
  OLED_MOSI,
  OLED_CLK,
  OLED_DC,
  OLED_RST,
  OLED_CS
);

  void setup(){
    Serial.begin(9600);
    Serial.println("Program Started");
    Wire.begin();
    Serial.println("I2C Started");
        if (bmp.begin(0x76))
        {
          Serial.println("BMP280 Found at 0x76");
        }
        else if (bmp.begin(0x77))
        {
          Serial.println("BMP280 Found at 0x77");
        }
        else {
          Serial.println("BMP280 Not Found");
        }
    display.begin(
      SSD1306_SWITCHCAPVCC
    );
    // Clear Display 
    display.clearDisplay();
    // Set Text Size 
    display.setTextSize(1);
    // Set Text Color 
    display.setTextColor(SSD1306_WHITE);
    // Update Display 
    display.display();
  }

  void loop(){
    
    // Read the temperature from the BMP280 sensor 
    temperature = bmp.readTemperature();
     // Read the Altitude from the BMP280 sensor 
    Altitude = bmp.readAltitude(1013.25);
    // Read the atmospheric pressure from the BMP280 sensor  
    pressure=bmp.readPressure()/ 100 ;
    // Clear the OLED display 
    display.clearDisplay(); 
    // Move the cursor to the top of the display 
    display.setCursor(0,0);
    // Display the label "Temp:" 
    display.print("Temp:");
    // Display the temperature value   
    display.print(temperature);
    // Display the temperature unit 
    display.println("C");

   // Display the label "Alt:"
    display.print("Alt:");
    // display the Atitude value
    display.print(Altitude); 
    // display the Atitude unit 
    display.println("m");
    
    // Read the atmospheric pressure from the BMP280 sensor  
    pressure=bmp.readPressure()/ 100 ;
    // display the label "pres:"   
    display.print("Pres:");
    // display the pressure value 
    display.print(pressure);
    // display the pressure unit 
    display.println("hPa");
     
   
    // update OLED 
    display.display();

    // Wait one second 
    delay(1000);
  }