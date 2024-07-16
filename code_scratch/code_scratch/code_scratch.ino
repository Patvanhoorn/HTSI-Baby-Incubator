#include "definitions.h" //Importing the header file
#include <Ticker.h> //For the tickers
#include <Adafruit_Sensor.h> 

#include <OneWire.h> // OneWire by Jim Studt, Tom Pollard ... v2.3.8
#include <DallasTemperature.h> //DallasTemperature by miles burton v.3.9.0


#include <DHT.h> //For the DHT snesors <DHT sensor library by Adafruit v1.4.6>
#include <DHT_U.h>


// For OLED
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h> //<Adafruit GFX Library by Adafruit v1.11.9>
#include <Adafruit_SSD1306.h>// <Adafruit SSD1306 by Adafruit v2.5.10>

Ticker sensorRead(readSensor, 2000);  //Ticker to avoid delay functions
DHT_Unified dht(DHT_PIN, DHTTYPE); //Temperature Sensor

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Screen  setup

DeviceAddress thermometerAddress;     // custom array type to hold 64 bit device address for pulse meter
OneWire oneWire(ONE_WIRE_BUS);        // create a oneWire instance to communicate with temperature IC
DallasTemperature tempSensor(&oneWire);  // pass the oneWire reference to Dallas Temperature



void setup() {
//Setting up serial communication.
  Serial.begin(9600);
  Serial.println("Setting Up");
// put your setup code here, to run once:
  pinMode(DHT_PIN, INPUT);
  pinMode(TEMP_PID, OUTPUT); //Define all pins 
  pinMode(fans,   OUTPUT);
  pinMode(heating, OUTPUT);
  pinMode(cooling, OUTPUT);
  pinMode(thermoregulation, OUTPUT); 
  pinMode(humidifier, OUTPUT);
  
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(moisture_sensor, INPUT);

//Using the DHT library and setting it up
  dht.begin();



  TCCR2B = (TCCR2B & B11111000) | 0x03;    // pin 3 PWM frequency of 928.5 Hz -- brackets added to exclude pin 11
  Time = millis();

  sensorRead.start(); //Start the ticker for sensor printing

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  Serial.println("DS18B20 Temperature IC Test");
  Serial.println("Locating devices...");
  tempSensor.begin();                         // initialize the temp sensor

  if (!tempSensor.getAddress(thermometerAddress, 0))
    Serial.println("Unable to find skin temp sensor.");
  else {
    Serial.print("Skin temp address: "); 
    printAddress(thermometerAddress); //Print the address of the sensor in serial.
    Serial.println();
  }
  tempSensor.setResolution(thermometerAddress, 11);      // set the temperature resolution (9-12)


  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  delay(2000);  
}

void loop() {
  // put your main code here, to run repeatedly:
  //Add a time since last reading 
  
  sensorRead.update(); //Update ticker

}

