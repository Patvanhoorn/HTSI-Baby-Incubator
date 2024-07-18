
//Display updates should occur more slowly in order to speed up the rest of the program. Only an intterupt for a error should call this fast

void display_update(){
//Set the display up
  display.display(); 
  display.fillRect(0, 0, SCREEN_WIDTH, 50, SSD1306_BLACK); 
  display.setTextSize(1);      // Normal 1:1 pixel scale 
  display.setTextColor(SSD1306_WHITE); // Draw white text 
  
  display.setCursor(0, 0);     // Start at top-left corner 
  display.print("Temperature: "); //Temperature on the 1st line
  display.print(DHTTempAV);
  display.drawCircle(111, 2, 1.75, WHITE);
  display.println(" C");

  display.setCursor(0, 10);
  display.print("Humidity: "); //Humidity on the 2nd line
  display.print(DHTHumAV);
  display.println("%");

  display.setCursor(0, 20);
  display.print("Skin Temp: "); //Display skintemp on the 3rd line
  display.print(calculateAverage(Skintemp));
  display.drawCircle(111, 2, 1.75, WHITE);
  display.println(" C");

  display.setCursor(0, 30);  
  display.print("Heart: "); // Display heart rate and SpO2
  display.print(calculateAverage(heartbeat));
  display.print(" bpm, SpO2: ");
  display.print(calculateAverage(spo2));
  display.println("%");

  display.drawFastHLine(0, 39, SCREEN_WIDTH, WHITE);
  display.setCursor(0, 40);  
  int waterAvaliable = digitalRead(waterlevel);
  if (waterAvaliable == LOW) {
    display.println("Liquid detected");
  } 
  else {
    display.println("No liquid detected");
  }


  
  
  
  display.display(); 
}

void display_error(){   //Called in readSensor()
  display2.display(); 
  display2.fillRect(0, 0, SCREEN_WIDTH, 10, SSD1306_BLACK); //Black out the 1st line    
  display2.setTextSize(1);      // Normal 1:1 pixel scale 
  display2.setTextColor(SSD1306_WHITE); // Draw white text 

  display2.setCursor(0, 0);  //1st line
  display2.println("Check temperature sensor(DHT22)");
  display2.display();
  //Possibly add a buzzer here
}
void display_dsberror(){      //Called in SkinTemp_Read()  
  display2.display(); 
  display2.fillRect(0, 10, SCREEN_WIDTH, 10, SSD1306_BLACK); //Black out the 2nd line    
  display2.setTextSize(1);      // Normal 1:1 pixel scale 
  display2.setTextColor(SSD1306_WHITE); // Draw white text 
  display2.setCursor(0, 10);     // Start at top-left corner 
  display2.println("!!Skin Probe!!");
  display2.display();
  //Possibly add a buzzer here
}
void display_temperror(){ //Called in register_update()
  display2.display(); 
  display2.fillRect(0, 20, SCREEN_WIDTH, 10, SSD1306_BLACK); //Black out the 2nd line    
  display2.setTextSize(1);      // Normal 1:1 pixel scale 
  display2.setTextColor(SSD1306_WHITE); // Draw white text 
  display2.setCursor(0, 20);     // Start at top-left corner 
  display2.println("!!Temperature Error!!");
  display2.display();
}
void display_humidityerror(){
  display2.display(); 
  display2.fillRect(0, 30, SCREEN_WIDTH, 10, SSD1306_BLACK); //Black out the 2nd line    
  display2.setTextSize(1);      // Normal 1:1 pixel scale 
  display2.setTextColor(SSD1306_WHITE); // Draw white text 
  display2.setCursor(0, 20);     // Start at top-left corner 
  display2.println("!!Humidity Error!!");
  display2.display();
}

void register_update(){ //Called in register_update()
leds = B00000001;
  if ( temperature >= 39 | temperature <= 36){
      leds |= B00000010;
     display_temperror();

    }
  if (humidity >= 100 | humidity <= 0){
    leds |= B00000010;
    display_humidityerror();
  } 
// if water level,skin temp,heartbeat,low oxygen... {leds |= B00000100;}

//Send data over to register
digitalWrite(LATCH_PIN, LOW);  //Latch off
shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, leds); //Write the data into the register
digitalWrite(LATCH_PIN, HIGH); //Latch on
  
}

// void printAddress(DeviceAddress deviceAddress)
// {
//   for (uint8_t i = 0; i < 8; i++)
//   {
//     if (deviceAddress[i] < 16) Serial.print("0");
//     Serial.print(deviceAddress[i], HEX);
//   }
// }