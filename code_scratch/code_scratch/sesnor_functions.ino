void readSensor(){

sensors_event_t event;
// Get temperature event and print its value if there is no error.
dht.temperature().getEvent(&event); 

  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
    dhterror = true; //Set error bool
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    temperature = event.temperature; //Update temperature variable
    Serial.println(F("°C"));
    Serial.print("TempTime: ");
    Serial.println(Time);
  }

// Get humidity event and print its value if there is no error.
dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
    dhterror = true;
  }
  else {
    Serial.print(F("Humidity: "));
    humidity = event.relative_humidity;
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
    Serial.print("HumTime: ");
    Serial.println(Time);
  } 
  tempSensor.requestTemperatures();
  skin_temperature = tempSensor.getTempC(thermometerAddress);
  Serial.print("Skin temperature");
  Serial.print(skin_temperature);
  Serial.print("°");
  Serial.println("C  ");

  if (dhterror == false){
    Serial.println("Updating PID and Display");
    PID_control();
    display_update();
    error_counter = 0; //Set the successive error count to 0
  }
  
  else{
    error_counter = error_counter + 1;
    dhterror = false;
    if (error_counter >= 5){ //If the error has occured 5 or more times in a row, display an error.
      display_error();
    }
  }



}