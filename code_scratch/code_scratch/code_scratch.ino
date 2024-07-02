#include <DHT11.h>
#include <Ticker.h>
#include "definitions.h"
//#include <PID_v2.h>

//This is going to git!!

DHT11 dht11(12); //DHT pin 12
//PID_v2 myPID(Kp, Ki, Kd, PID::Direct);// For PID
Ticker printSensors(sensor_read,1); //Ticker

void setup() {
  // put your setup code here, to run once:
pinMode(TEMP_PID, OUTPUT);
pinMode(fans, OUTPUT);
pinMode(heating, OUTPUT);
pinMode(cooling, OUTPUT);
pinMode(thermoregulation, OUTPUT); //Define all pins
pinMode(humidifier, OUTPUT);
pinMode(moisture_sensor, INPUT);


TCCR2B = (TCCR2B & B11111000) | 0x03;    // pin 3 PWM frequency of 928.5 Hz -- brackets added to exclude pin 11
Time = millis();

int temp = dht11.readTemperature();  //Get an initial value
int humi = dht11.readHumidity();

printSensors.start(); //Start the ticker for sensor printing

Serial.begin(9600);
Serial.println("Setting Up");
}

void loop() {
  // put your main code here, to run repeatedly:
  //Add a time since last reading 
  
  printSensors.update(); //Update ticker

}

