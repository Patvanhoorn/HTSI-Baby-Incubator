
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
    display.println("");
  } 
  else {
    display.println("No liquid detected");
  }

  display.display(); 
}

void display_DHTerror(){   //Called in readSensor() - Occurs if DHT sensors fail to work
  display2.display(); 
  display2.fillRect(0, 0, SCREEN_WIDTH, 8, SSD1306_BLACK); //Black out the 1st line    
  display2.setTextSize(1);      // Normal 1:1 pixel scale 
  display2.setTextColor(SSD1306_WHITE); // Draw white text 
  display2.setCursor(0, 0);  //1st line
  display2.println("!!DHTs!!");
  display2.display();
}
void display_dsberror(){      //Called in register_update()
  display2.display(); 
  display2.fillRect(0, 8, SCREEN_WIDTH,8, SSD1306_BLACK); //Black out the 2nd line    
  display2.setTextSize(1);      // Normal 1:1 pixel scale 
  display2.setTextColor(SSD1306_WHITE); // Draw white text 
  display2.setCursor(0, 8);     // Start at top-left corner 
  display2.println("!!Skin Probe!!");
  display2.display();
}
//Water sensor error needs to be added 
//Oximeter sensor error needs to be added

void display_tempcheck(){ //Called in register_update()  - Heating check
  display2.display(); 
  display2.fillRect(0, 16, SCREEN_WIDTH, 8, SSD1306_BLACK); //Black out the 2nd line    
  display2.setTextSize(1);      // Normal 1:1 pixel scale 
  display2.setTextColor(SSD1306_WHITE); // Draw white text 
  display2.setCursor(0, 16);     // Start at top-left corner 
  display2.println("!Check Air Temp");
  display2.display();
}

void display_skintempcheck(){ //Called in register_update()  - Heating check
  display2.display(); 
  display2.fillRect(0, 24, SCREEN_WIDTH, 8, SSD1306_BLACK); //Black out the 2nd line    
  display2.setTextSize(1);      // Normal 1:1 pixel scale 
  display2.setTextColor(SSD1306_WHITE); // Draw white text 
  display2.setCursor(0, 24);     // Start at top-left corner 
  display2.println("!Check Skin Probe");
  display2.display();
}

void display_humidityerror(){ //Occurs when humidity values are out of bounds - Sensor error
  display2.display(); 
  display2.fillRect(0, 32, SCREEN_WIDTH, 8, SSD1306_BLACK); //Black out the 2nd line    
  display2.setTextSize(1);      // Normal 1:1 pixel scale 
  display2.setTextColor(SSD1306_WHITE); // Draw white text 
  display2.setCursor(0, 32);     // Start at top-left corner 
  display2.println("!Check Humidity");
  display2.display();
}

void display_heartcheck(){
  display2.display(); 
  display2.fillRect(0, 40, SCREEN_WIDTH, 8, SSD1306_BLACK); //Black out the 2nd line    
  display2.setTextSize(1);      // Normal 1:1 pixel scale 
  display2.setTextColor(SSD1306_WHITE); // Draw white text 
  display2.setCursor(0, 40);     // Start at top-left corner 
  display2.println("!Check Heartbeat");
  display2.display();
}

void display_o2check(){
  display2.display(); 
  display2.fillRect(0, 48, SCREEN_WIDTH, 8, SSD1306_BLACK); //Black out the 2nd line    
  display2.setTextSize(1);      // Normal 1:1 pixel scale 
  display2.setTextColor(SSD1306_WHITE); // Draw white text 
  display2.setCursor(0, 48);     // Start at top-left corner 
  display2.println("!Check Baby");
  display2.display();
}

void display_roomTemp(){
  display2.display(); 
  display2.fillRect(0, 56, SCREEN_WIDTH, 8, SSD1306_BLACK); //Black out the 2nd line    
  display2.setTextSize(1);      // Normal 1:1 pixel scale 
  display2.setTextColor(SSD1306_WHITE); // Draw white text 
  display2.setCursor(0, 56);     // Start at top-left corner 
  display2.println("!Check airflow");
  display2.display();
}
void register_update(){ //Called in register_update()
//Possibly add a buzzer here activate the buzzer of either bit 1 or 2 is 1
leds = B00000001;
//Buzzer B00001000
//Yellow led B00000100
//Red led B00000010
//On led B00000001
  if (error_counter >= 5){ //If the error in the DHT has occured 5 or more times in a row, display an error.
      display_DHTerror();
      leds |= B00000010;
  }
  if (skin_error_counter >= 5){
      display_dsberror();
      leds |= B00000010;
  }
//Water sensor error needs to be added 
//Oximeter sensor error needs to be added
  if ( DHTTempAV >= temperature_ref +2  || DHTTempAV <= temperature_ref - 2){ //If temperature deviates from the reference +- 2 degrees set a warning
     display_tempcheck();
     leds |= B00000100;
  }

  if (calculateAverage(Skintemp) >= 37.5 || calculateAverage(Skintemp) <=35.5){
    display_skintempcheck();
    leds |= B00000100;
  }
  if (DHTHumAV >= 80 || DHTHumAV <= 70){
    leds |= B00000100;
    display_humidityerror();
  } 

  if(calculateAverage(heartbeat) < 50 || calculateAverage(heartbeat) >110){ //For adults testing
 // if(calculateAverage(heartbeat) < 90 || calculateAverage(heartbeat) >200){ //For babies 
    leds |= B00000100;
    display_heartcheck();
  }
 
  if(calculateAverage(spo2)<90){
    leds |= B00000100;
    display_o2check();
  }
  float maxVal = max(max(max(calculateAverage(DHT1temp), calculateAverage(DHT2temp)), calculateAverage(DHT3temp)), max(calculateAverage(DHT4temp), calculateAverage(DHT5temp)));
  float minVal = min(min(min(calculateAverage(DHT1temp), calculateAverage(DHT2temp)), calculateAverage(DHT3temp)), min(calculateAverage(DHT4temp), calculateAverage(DHT5temp)));
  if(maxVal - minVal < 5){
    leds |= B00000100;
    display_roomTemp();
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