#include "definitions.h"
#include <Ticker.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
// for oled
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include <PID_v2.h>
//This is going to git!!!

//PID_v2 myPID(Kp, Ki, Kd, PID::Direct);// For PID

Ticker sensorRead(readSensor, 2000);
DHT_Unified dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // put your setup code here, to run once:
  pinMode(TEMP_PID, OUTPUT);
  pinMode(fans, OUTPUT);
  pinMode(heating, OUTPUT);
  pinMode(cooling, OUTPUT);
  pinMode(thermoregulation, OUTPUT); //Define all pins
  pinMode(humidifier, OUTPUT);
  pinMode(moisture_sensor, INPUT);

  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);


  TCCR2B = (TCCR2B & B11111000) | 0x03;    // pin 3 PWM frequency of 928.5 Hz -- brackets added to exclude pin 11
  Time = millis();

  sensorRead.start(); //Start the ticker for sensor printing

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

