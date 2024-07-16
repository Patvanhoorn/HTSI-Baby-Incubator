void display_update(){
//Set the display up
  display.display(); 
  display.clearDisplay(); 
  display.setTextSize(1);      // Normal 1:1 pixel scale 
  display.setTextColor(SSD1306_WHITE); // Draw white text 
  display.setCursor(0, 0);     // Start at top-left corner 

  display.print("Temperature: ");
  display.print(float(temperature));
  display.drawCircle(111, 2, 1.75, WHITE);
  display.println(" C");

  display.print("Humidity: ");
  display.print(int(humidity));
  display.println("%");


  display.display(); 

}

void display_error(){
  display.display(); 
  display.clearDisplay(); 
  display.setTextSize(2);      // Normal 1:1 pixel scale 
  display.setTextColor(SSD1306_WHITE); // Draw white text 
  display.setCursor(0, 0);     // Start at top-left corner 

  display.println("Temperature sensor(DHT22)");
  display.println("ERROR");
  display.println("RESTART");

  display.display();
  //Possibly add a buzzer here

}
void register_update(){
leds = B00000001;
  if ( temperature >= 39 | temperature <= 36){
    if (steady_state_temp = true){
      leds |= B00000010;
    }
  if (humidity >= 100 | humidity <= 0){
    leds |= B00000010;
  } 
// if water level,skin temp,heartbeat,low oxygen... {leds |= B00000100;}

//Send data over to register
digitalWrite(LATCH_PIN, LOW);  //Latch off
shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, leds); //Write the data into the register
digitalWrite(LATCH_PIN, HIGH); //Latch on
  }
}
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}