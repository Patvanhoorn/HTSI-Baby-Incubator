#include "definitions.h" //Importing the header file
#include <Ticker.h> //For the tickers
#include <Adafruit_Sensor.h> 

#include <OneWire.h> // OneWire by Jim Studt, Tom Pollard ... v2.3.8
#include <DallasTemperature.h> //DallasTemperature by miles burton v.3.9.0 For the sensor remember to put a pull up resistor

#include <DHT.h> //For the DHT snesors <DHT sensor library by Adafruit v1.4.6>
#include <DHT_U.h>

// For OLED
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h> //<Adafruit GFX Library by Adafruit v1.11.9>
#include <Adafruit_SSD1306.h>// <Adafruit SSD1306 by Adafruit v2.5.10>

#include "MAX30100_PulseOximeter.h" //<MAX30100_milan v1.3.0>

Ticker sensorRead(readSensor, 2000);  //Ticker to avoid delay functions
Ticker humControl(humidityControl, 5000); // changing led every 500ms
Ticker displayUpdate(display_update, 10000);
Ticker babyStats(oximeter,500);
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Screen  setup big
Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Screen  setup small

DeviceAddress thermometerAddress;     // custom array type to hold 64 bit device address for pulse meter
OneWire oneWire(ONE_WIRE_BUS);        // create a oneWire instance to communicate with temperature IC
DallasTemperature skintempSensor(&oneWire);  // pass the oneWire reference to Dallas Temperature
PulseOximeter pox;



void setup() {
//Setting up serial communication.
  Serial.begin(9600);
  Serial.println("Setting Up");

// put your setup code here, to run once:
  pinMode(padHeat, OUTPUT);
  pinMode(TEMP_PID, OUTPUT); //Define all pins 
  pinMode(fans,   OUTPUT);
  pinMode(heating, OUTPUT);
  pinMode(cooling, OUTPUT);
  pinMode(thermoregulation, OUTPUT); 
  pinMode(humidifier, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  //12 for DSB skin probe
  pinMode(waterlevel,INPUT_PULLUP);
  TCCR2B = (TCCR2B & B11111000) | 0x03;    // pin 3 PWM frequency of 928.5 Hz -- brackets added to exclude pin 11

  sensorRead.start(); //Start the ticker for sensor printing
  humControl.start(); //Start the ticker for humidity control
  displayUpdate.start(); //Start the ticker of display updates
  babyStats.start(); //Start the  ticker for oximeter updates

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64 SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    Serial.println(F("SSD1306 big allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  if(!display2.begin(SSD1306_SWITCHCAPVCC, 0x3D)) { // Address 0x3D for 128x64 SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    Serial.println(F("SSD1306 big allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  Serial.println("DS18B20 Temperature IC Test");
  Serial.println("Locating devices...");
  skintempSensor.begin();                         // initialize the temp sensor

  if (!skintempSensor.getAddress(thermometerAddress, 0)){
    Serial.println("Unable to find skin temp sensor.");
    for(;;);
  }
  else {
    Serial.print("Skin temp address: "); 
    //printAddress(thermometerAddress); //Print the address of the sensor in serial.
    Serial.println();
  }
  skintempSensor.setResolution(thermometerAddress, 11);      // set the temperature resolution (9-12)
  if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
  } 
  else {
        Serial.println("SUCCESS");
    }
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA); //Current into pox  



  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display2.clearDisplay();
  display2.setTextSize(1);
  display2.setTextColor(SSD1306_WHITE);


   for (int i = 0; i < 10; i++) {
    DHT_Read();
    SkinTemp_Read();
    oximeter();
  }
  delay(2000);  
}

void loop() {
  // put your main code here, to run repeatedly:
  //Add a time since last reading 
  humControl.update();//Update ticker
  sensorRead.update(); 
  displayUpdate.update();
  babyStats.update();
}

