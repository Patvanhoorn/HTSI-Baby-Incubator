#include "definitions.h" //Importing the header file
#include <Ticker.h> //For the tickers
#include <Adafruit_Sensor.h> 

#include <DHT.h> //For the DHT snesors <DHT sensor library by Adafruit v1.4.6>
#include <DHT_U.h>

// For OLED
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h> //<Adafruit GFX Library by Adafruit v1.11.9>
#include <Adafruit_SSD1306.h>// <Adafruit SSD1306 by Adafruit v2.5.10>

Ticker sensorRead(readSensor, 2000);  //Ticker to avoid delay functions
DHT_Unified dht(DHTPIN, DHTTYPE); //Temperature Sensor
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Screen 

void setup() {
  // put your setup code here, to run once:
  pinMode(TEMP_PID, OUTPUT); //Define all pins 
  pinMode(fans, OUTPUT);
  pinMode(heating, OUTPUT);
  pinMode(cooling, OUTPUT);
  pinMode(thermoregulation, OUTPUT); 
  pinMode(humidifier, OUTPUT);
  pinMode(moisture_sensor, INPUT);

  //Using the DHT library
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor); 


  TCCR2B = (TCCR2B & B11111000) | 0x03;    // pin 3 PWM frequency of 928.5 Hz -- brackets added to exclude pin 11
  Time = millis();

  sensorRead.start(); //Start the ticker for sensor printing

  //Setting up serial communication.
  Serial.begin(9600);
  Serial.println("Setting Up");

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  delay(2000);  
}

void loop() {
  // put your main code here, to run repeatedly:
  //Add a time since last reading 
  
  sensorRead.update(); //Update ticker

}

