
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 2     // Digital pin connected to the DHT sensor 
#define DHTTYPE    DHT22     // DHT 22 (AM2302)

int counter = 0;
DHT_Unified dht(DHTPIN, DHTTYPE);

const int latchPin = 9;  // latch pin for both shift registers
const int clockPin = 10; // clock pin for both shift registers
const int dataPin1 = 11;  // data pin for first shift register

byte outOn = 0;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);  
  pinMode(dataPin1, OUTPUT);
  Serial.begin(9600); // Initialize serial communication at 9600 baud
  dht.begin();
  Serial.println("Setting up");
  digitalWrite(latchPin, LOW);
  shiftOut(0, clockPin, MSBFIRST, outOn);
  digitalWrite(latchPin, HIGH);
  delay(2000);
}

void loop() {

    if (counter == 1){
      counter = 0;
      }
    else{
      counter = counter + 1;
      }


for (int i = 0; i < counter+1; i++) {
    outOn = 1 << i; }// Shift the bit to the left by i positions}
  Serial.println(outOn);


digitalWrite(latchPin, LOW);
shiftOut(dataPin1, clockPin, MSBFIRST, B00000001);
digitalWrite(latchPin, HIGH);
readTemp();


digitalWrite(latchPin, LOW);
shiftOut(dataPin1, clockPin, MSBFIRST, B00000010);
digitalWrite(latchPin, HIGH);
readTemp();


}

void readTemp(){
  // Delay between measurements.
  delay(2000);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }
}
