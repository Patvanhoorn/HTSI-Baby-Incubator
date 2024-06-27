#include <SPI.h> 
#include <Wire.h> 
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h>
#include <DHT11.h>
  
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);//新建显示屏对象
DHT11 dht11_air(12);    // dht11 (air sensor)
DHT11 dht11_plate(13);  // dht11 (plate sensor)

#define water_low 300
#define water_high 550

static const unsigned char PROGMEM wen[]= {
0x00,0x00,0x23,0xF8,0x12,0x08,0x12,0x08,0x83,0xF8,0x42,0x08,0x42,0x08,0x13,0xF8,
0x10,0x00,0x27,0xFC,0xE4,0xA4,0x24,0xA4,0x24,0xA4,0x24,0xA4,0x2F,0xFE,0x00,0x00
};
//度
static const unsigned char PROGMEM du[]= {
0x01,0x00,0x00,0x80,0x3F,0xFE,0x22,0x20,0x22,0x20,0x3F,0xFC,0x22,0x20,0x22,0x20,
0x23,0xE0,0x20,0x00,0x2F,0xF0,0x24,0x10,0x42,0x20,0x41,0xC0,0x86,0x30,0x38,0x0E
};
//湿
static const unsigned char PROGMEM shi[]= {
0x00,0x00,0x27,0xF8,0x14,0x08,0x14,0x08,0x87,0xF8,0x44,0x08,0x44,0x08,0x17,0xF8,
0x11,0x20,0x21,0x20,0xE9,0x24,0x25,0x28,0x23,0x30,0x21,0x20,0x2F,0xFE,0x00,0x00
};
//℃
static const unsigned char PROGMEM C[]= {
0x60,0x00,0x91,0xF4,0x96,0x0C,0x6C,0x04,0x08,0x04,0x18,0x00,0x18,0x00,0x18,0x00,
0x18,0x00,0x18,0x00,0x18,0x00,0x08,0x00,0x0C,0x04,0x06,0x08,0x01,0xF0,0x00,0x00
};

static const unsigned char PROGMEM shui[]={
  0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x08,0x01,0x08,0x7D,0x90,0x05,0xA0,0x09,0x40,
  0x09,0x40,0x11,0x20,0x11,0x10,0x21,0x08,0x41,0x06,0x81,0x00,0x05,0x00,0x02,0x00};/*"水",0*/

static const unsigned char PROGMEM liang[]={
  0x00,0x00,0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x10,0x10,0xFF,0xFE,0x00,0x00,0x1F,0xF0,
  0x11,0x10,0x1F,0xF0,0x11,0x10,0x1F,0xF0,0x01,0x00,0x1F,0xF0,0x01,0x00,0x7F,0xFC};/*"量",1*/

static const unsigned char PROGMEM wei[]={
  0x08,0x80,0x08,0x40,0x08,0x40,0x10,0x00,0x17,0xFC,0x30,0x00,0x30,0x08,0x52,0x08,
  0x92,0x08,0x11,0x10,0x11,0x10,0x11,0x10,0x11,0x20,0x10,0x20,0x1F,0xFE,0x10,0x00};/*"位",2*/


// Basic functions
void display_string(int16_t x, int16_t y,char *c, uint8_t size)
{
  int16_t cnt=0;
  while(*c)
  {
    display.drawChar(x+cnt*8, y, *c, 1,0, size);
    cnt++;
    c++;
  }
}
void uart_clear()
{
  int len,i;
  len = Serial.available();//获取串口数据长度
  for(i=0;i<len;i++)//读取所有串口数据
  {
    Serial.read();
  }
}
void LED_ON()
{
  digitalWrite(LED_BUILTIN, HIGH);
}
void LED_OFF()
{
  digitalWrite(LED_BUILTIN, LOW);
}
void heat_on()
{
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
}
void heat_off()
{
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}
void cool_on()
{
  digitalWrite(8, HIGH);
  digitalWrite(10, LOW);
}
void cool_off()
{
  digitalWrite(8, LOW);
  digitalWrite(10, LOW);
}
void humidification_on()
{
  digitalWrite(11, HIGH);
}
void humidification_off()
{
  digitalWrite(11, LOW);
}


// Setup code
void setup() {  
  Serial.begin(115200);   // initialize serial port
  pinMode(A0,INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(8, OUTPUT);   // semiconductor cooling plate
  pinMode(9, OUTPUT);   // heating fan
  pinMode(10, OUTPUT);  // cooling fan
  pinMode(11, OUTPUT);  // humidifier
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize display
  display.clearDisplay();                     // clear display
  display.setTextSize(2);                     // font size
  display.setTextColor(WHITE);                // font colour

  display.display();

  // delay(500);//等待wifi模块准备就绪
  delay(1000);

  // Serial.println("AT+CIPMUX=1");
  // delay(1000);
  // Serial.println("AT+CIPSERVER=1,8086");
  // delay(1000);
  uart_clear();
}

// Main code
void loop() {
  
  // define variables
  float temp_air, temp_plate, humi, water_value;
  int i, TEMP;
  static int count=0, heat_state=0, cool_state=0;
  char str[64];

  if(count>=8)
  {
    count=0;

    // Get readings
    temp_air = dht11_air.readTemperature();
    temp_plate = dht11_plate.readTemperature();
    humi = dht11_air.readHumidity();
    water_value = analogRead(A0);

    Serial.println(temp_plate);

    water_value = (water_value-water_low)*100.0/(water_high-water_low);   // convert to %
    if(water_value>100)   // set upper limit for water value
      water_value=100;
    if(water_value<0)     // set lower limit for water value
      water_value=0;
    if(temp_air<0)            // set lower limit for temp
      temp_air=0;

    // Display readings
    display.clearDisplay();//清屏
    display.drawBitmap(0, 0, wen, 16, 16, 1);//温
    display.drawBitmap(16, 0, du, 16, 16, 1);//度
    display.drawChar(32, 4, ':', 1,0, 2);
    display.setCursor(32,4);//在32,4坐标处显示冒号
    display.print(":");
    display.setCursor(40,0);
    display.print(temp_air,1);
    display.drawBitmap(90,0,C,16,16,1);//x坐标0，y坐标0,宽度，高度，编码word1

    display.drawBitmap(0, 16, shi, 16, 16, 1); //湿
    display.drawBitmap(16, 16, du, 16, 16, 1); //度
    display.drawChar(32, 20, ':', 1,0, 2);
    // display.setCursor(32,20);
    // display.print(":");
    display.setCursor(40,16);
    display.print(int(humi));
    display.setCursor(72,16);
    display.print("%");

    display.drawBitmap(0, 32, shui, 16, 16, 1); //水
    display.drawBitmap(16, 32, liang, 16, 16, 1); //量
    //display.drawBitmap(16, 32, 位, 16, 16, 1); //量
    display.drawChar(32, 36, ':', 1,0, 2);
    display.setCursor(40,32);
    display.print(int(water_value));
    display.setCursor(72,32);
    display.print("%");

    display.display();

    // Manage heating/cooling
    if(temp_air<36)
    {
      heat_on();
      heat_state=1;
    }
    else if(temp_air<37 && cool_state)
    {
      cool_off();
      cool_state=0;
    }
    else if(temp_air>37 && heat_state)
    {
      heat_off();
      heat_state=0;
    }
    else if(temp_air>38)
    {
      cool_on();
      cool_state=1;
    }
    else
    {
      heat_off();
      heat_state=0;
      cool_off();
      cool_state=0;
    }

    // Manage humidity
    if(humi<=75)
    {
      humidification_on();
    }
    else if(humi>85)
    {
      humidification_off();
    }

  }
  count++;
  delay(100);
}
