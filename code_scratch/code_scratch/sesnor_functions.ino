void readSensor(){
 /* result = dht11.readTemperatureHumidity(temperature, humidity); //Read values
    if (result == 0) {
      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.print(" °C\tHumidity: ");
      Serial.print(humidity);
      Serial.println(" %");
      PID_control();
    } else {
        // Print error message based on the error code.
        Serial.println(DHT11::getErrorString(result)); 
    }*/
  
  display.clearDisplay(); 
  display.setTextSize(1);      // Normal 1:1 pixel scale 
  display.setTextColor(SSD1306_WHITE); // Draw white text 
  display.setCursor(0, 0);     // Start at top-left corner 

  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
    display.println("Error reading temperature!");
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    temperature = event.temperature;
    Serial.println(F("°C"));

    display.print("Temperature: ");
    display.print(temperature);
    display.drawCircle(92, 2, 1.75, WHITE);
    display.println(" C");
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    humidity = event.relative_humidity;
    Serial.println(F("Error reading humidity!"));
    display.println("Error reading humidity!");
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
    dhterror = true;

    int humidity = 75;
    display.print("Humidity: ");
    display.print(humidity);
    display.println("%\n");
  } 
  if (dhterror = false){
    PID_control();
  }
  else{
    dhterror = false;
  }

  if (steady_state_temp = false) {
    if (temperature = temperature_ref) {
      steady_state_temp = true
    }
  }

  // Display image 
  display.display(); 

}