#include <DHT11.h>
#include <Ticker.h>
#include "definitions.h"
#include <PID_v2.h>

//This is going to git!!

DHT11 dht11(12); //DHT pin 12
PID_v2 myPID(Kp, Ki, Kd, PID::Direct);// For PID
Ticker printSensors(sensor_read,1); //Ticker

void setup() {
  // put your setup code here, to run once:
pinMode(heat_supply, OUTPUT); //Define all pins
pinMode(fan1, OUTPUT);
pinMode(fan2, OUTPUT);
pinMode(humidifier, OUTPUT);
pinMode(moisture_sensor, INPUT);
pinMode(TEST_LED,OUTPUT);

int temp = dht11.readTemperature();  //Get an initial value
int humi = dht11.readHumidity();

printSensors.start(); //Start the ticker for sensor printing

Serial.begin(9600);
Serial.println("Setting Up");
}

void loop() {
  // put your main code here, to run repeatedly:
  //Add a time since last reading 
  result = dht11.readTemperatureHumidity(temperature, humidity); //Read values
  printSensors.update(); //Update ticker
  digitalWrite(fan1, HIGH);
  digitalWrite(fan2, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(8, HIGH);
}

