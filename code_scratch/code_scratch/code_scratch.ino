#include <DHT11.h>
#include <Ticker.h>
#include "definitions.h"


DHT11 dht11(12); //DHT pin 12

Ticker printSensors(sensor_read,1); //Ticker

void sensor_read(){
  if (result == 0) {
        Serial.print("Temperature: ");  //Print sensor readings
        Serial.print(temperature);
        Serial.print(" °C\tHumidity: ");
        Serial.print(humidity);
        Serial.println(" %");
        } 
  if (result == DHT11::ERROR_CHECKSUM && result == DHT11::ERROR_TIMEOUT) {
        // Print error message based on the error code.
    Serial.print("Here");
    Serial.println(DHT11::getErrorString(result));
    }
}


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
  result = dht11.readTemperatureHumidity(temperature, humidity); //Read values
  printSensors.update(); //Update ticker
  delay(5000);
  digitalWrite(fan1, HIGH);
  digitalWrite(fan2, HIGH);
}

