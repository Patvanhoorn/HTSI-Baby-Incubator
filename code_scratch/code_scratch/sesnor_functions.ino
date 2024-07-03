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
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    temperature = event.temperature;
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    humidity = event.relative_humidity;
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
    dhterror = true;
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

}