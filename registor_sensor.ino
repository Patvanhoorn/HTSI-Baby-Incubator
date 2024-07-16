#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <MAX30105.h>
#include <heartRate.h>

// Define sensor pins
#define DHT1_PIN 2
#define DHT2_PIN 3
#define DHT3_PIN 4
#define DHT4_PIN 5
#define DS18B20_PIN 6
#define MAX30105_PIN 7

// DHT sensor instances
DHT dht1(DHT1_PIN, DHT11);
DHT dht2(DHT2_PIN, DHT11);
DHT dht3(DHT3_PIN, DHT11);
DHT dht4(DHT4_PIN, DHT11);

// DS18B20 sensor instance
OneWire oneWire(DS18B20_PIN);
DallasTemperature ds18b20(&oneWire);

// MAX30105 sensor instance
MAX30105 max30105;

// Sensor data variables
float dht1_temp, dht1_humidity;
float dht2_temp, dht2_humidity;
float dht3_temp, dht3_humidity;
float dht4_temp, dht4_humidity;
float ds18b20_temp;
uint32_t max30105_red, max30105_ir;
float max30105_spo2, max30105_heartrate;

// Sensor control bitmask
uint8_t sensor_mask = 0b000001; // Start with DHT1

void setup() {
  Serial.begin(9600);

  // Initialize DHT sensors
  dht1.begin();
  dht2.begin();
  dht3.begin();
  dht4.begin();

  // Initialize DS18B20 sensor
  ds18b20.begin();

  // Initialize MAX30105 sensor
  if (!max30105.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("MAX30105 not detected.");
  }
  max30105.setup(); // Configure sensor with default settings
}

void loop() {
  // Turn on the current sensor
  switch (sensor_mask) {
    case 0b000001:
      dht1.readTemperatureAndHumidity(&dht1_temp, &dht1_humidity);
      break;
    case 0b000010:
      dht2.readTemperatureAndHumidity(&dht2_temp, &dht2_humidity);
      break;
    case 0b000100:
      dht3.readTemperatureAndHumidity(&dht3_temp, &dht3_humidity);
      break;
    case 0b001000:
      dht4.readTemperatureAndHumidity(&dht4_temp, &dht4_humidity);
      break;
    case 0b010000:
      ds18b20.requestTemperatures();
      ds18b20_temp = ds18b20.getTempCByIndex(0);
      break;
    case 0b100000:
      max30105.check();
      max30105_red = max30105.getRed();
      max30105_ir = max30105.getIR();
      max30105_spo2 = MAX30105_計算_SpO2(max30105_red, max30105_ir);
      max30105_heartrate = MAX30105_計算_HeartRate(max30105_red, max30105_ir);
      break;
  }

  // Print the sensor data
  printSensorData();

  // Turn off the current sensor
  switch (sensor_mask) {
    case 0b000001:
      dht1.end();
      break;
    case 0b000010:
      dht2.end();
      break;
    case 0b000100:
      dht3.end();
      break;
    case 0b001000:
      dht4.end();
      break;
    case 0b010000:
      // No need to turn off DS18B20
      break;
    case 0b100000:
      // No need to turn off MAX30105
      break;
  }

  // Move to the next sensor
  sensor_mask <<= 1;
  if (sensor_mask > 0b100000) {
    sensor_mask = 0b000001; // Restart the cycle
  }

  delay(1000); // Wait for 1 second before the next sensor reading
}

void printSensorData() {
  Serial.println("Sensor Data:");
  switch (sensor_mask) {
    case 0b000001:
      Serial.print("DHT1: Temp=");
      Serial.print(dht1_temp);
      Serial.print(", Humidity=");
      Serial.println(dht1_humidity);
      break;
    case 0b000010:
      Serial.print("DHT2: Temp=");
      Serial.print(dht2_temp);
      Serial.print(", Humidity=");
      Serial.println(dht2_humidity);
      break;
    case 0b000100:
      Serial.print("DHT3: Temp=");
      Serial.print(dht3_temp);
      Serial.print(", Humidity=");
      Serial.println(dht3_humidity);
      break;
    case 0b001000:
      Serial.print("DHT4: Temp=");
      Serial.print(dht4_temp);
      Serial.print(", Humidity=");
      Serial.println(dht4_humidity);
      break;
    case 0b010000:
      Serial.print("DS18B20: Temp=");
      Serial.println(ds18b20_temp);
      break;
    case 0b100000:
      Serial.print("MAX30105: Red=");
      Serial.print(max30105_red);
      Serial.print(", IR=");
      Serial.print(max30105_ir);
      Serial.print(", SpO2=");
      Serial.print(max30105_spo2);
      Serial.print(", Heartrate=");
      Serial.println(max30105_heartrate);
      break;
  }
  Serial.println();
}