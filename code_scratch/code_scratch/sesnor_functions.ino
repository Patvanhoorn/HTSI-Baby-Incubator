void readSensor(){
  //Set the display up
  display.display(); 
  display.clearDisplay(); 
  display.setTextSize(1);      // Normal 1:1 pixel scale 
  display.setTextColor(SSD1306_WHITE); // Draw white text 
  display.setCursor(0, 0);     // Start at top-left corner 

  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
    // display.println("Error reading temperature!");
    display.println("Error1");
    dhterror = true;
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    temperature = event.temperature;
    Serial.println(F("°C"));
    Serial.print("TempTime: ");
    Serial.println(Time);

    display.print("Temperature: ");
    display.print(float(temperature));
    display.drawCircle(111, 2, 1.75, WHITE);
    display.println(" C");
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
    // display.println("Error reading humidity!");
    dhterror = true;
    display.println("Error2");
  }
  else {
    Serial.print(F("Humidity: "));
    humidity = event.relative_humidity;
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
    Serial.print("HumTime: ");
    Serial.println(Time);

    display.print("Humidity: ");
    display.print(int(humidity));
    display.println("%");
  } 
  if (dhterror == false){
    PID_control();
    Serial.println("entering PID control");
  }
  else{
    dhterror = false;
  }
  // Display image 
  display.display(); 
}