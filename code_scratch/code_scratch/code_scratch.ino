#include "definitions.h" //Importing the header file
#include <Ticker.h> //Install <Ticker by Stefan Staub v4.4.0>
#include <Adafruit_Sensor.h> 

#include <OneWire.h> // Install <OneWire by Jim Studt, Tom Pollard ... v2.3.8>
#include <DallasTemperature.h> // Install <DallasTemperature by miles burton v.3.9.0>  For the sensor remember to put a pull up resistor

#include <DHT.h> //Install <DHT sensor library by Adafruit v1.4.6>   for DHT sensors
#include <DHT_U.h>

// For OLED
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h> //Install <Adafruit GFX Library by Adafruit v1.11.9>
#include <Adafruit_SSD1306.h>//Install  <Adafruit SSD1306 by Adafruit v2.5.10>

#include "MAX30100_PulseOximeter.h" //Install <MAX30100_milan by OXullo v1.3.0>

Ticker sensorRead(readSensor, 2100);  //Ticker to avoid delay functions
Ticker humControl(humidityControl, 4900); // changing led every 500ms
Ticker displayUpdate(display_update, 10000);
Ticker babyStats(oximeter,450);
Ticker errorLEDs(register_update,4500);
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Screen  setup big
Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Screen  setup small

DeviceAddress thermometerAddress;     // custom array type to hold 64 bit device address for pulse meter
OneWire oneWire(ONE_WIRE_BUS);        // create a oneWire instance to communicate with temperature IC
DallasTemperature skintempSensor(&oneWire);  // pass the oneWire reference to Dallas Temperature
PulseOximeter pox;

uint32_t tsLastReport = 0;
#define REPORTING_PERIOD_MS     1000

DHT_Unified  dht(22, DHTTYPE);
DHT_Unified  dht2(23, DHTTYPE);
DHT_Unified  dht3(24, DHTTYPE);
DHT_Unified  dht4(25, DHTTYPE);


void setup() {
//Setting up serial communication.
  Serial.begin(9600);
  Serial.println(F("Setting Up"));

  dht.begin();
  dht2.begin();
  dht3.begin();
  dht4.begin();

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
  errorLEDs.start(); //Start the register ticker


  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally


  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 big allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  Serial.println(F("We are now here"));
  
  if(!display2.begin(SSD1306_SWITCHCAPVCC, 0x3D)) { // Address 0x3D for 128x64 SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    Serial.println(F("SSD1306 small allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  Serial.println(F("DS18B20 Temperature IC Test"));
  Serial.println(F("Locating devices..."));
  skintempSensor.begin();                         // initialize the temp sensor

  if (!skintempSensor.getAddress(thermometerAddress, 0)){
    Serial.println(F("Unable to find skin temp sensor."));
    for(;;);
  }
  else {
    Serial.print(F("Skin temp sensor found ")); 
    //printAddress(thermometerAddress); //Print the address of the sensor in serial.
  }
  skintempSensor.setResolution(thermometerAddress, 11);      // set the temperature resolution (9-12)
 
 
//  if (!pox.begin()) {
 //       Serial.println(F("FAILED"));
  //      for(;;);
 // } 
 // else {
 //       Serial.println(F("SUCCESS"));
 //   }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display2.clearDisplay();
  display2.setTextSize(1);
  display2.setTextColor(SSD1306_WHITE);
  display_startup();
  
   for (int i = 0; i < 10; i++) {
    DHT_Read();
    SkinTemp_Read();
    //oximeter();
   delay(2000);
  } 
  

  HighHeat();
  heat();

  Serial.println("Entering main loop");
}

void loop() {
  delay(2000);
  display_update();
 // analogWrite(TEMP_PID,255);
  DHT_Read();
  //oximeter();
  SkinTemp_Read();
  // put your main code here, to run repeatedly:


  // humControl.update();//Update ticker
  // sensorRead.update(); 
  // displayUpdate.update();
  // babyStats.update();
  // errorLEDs.update();
}

