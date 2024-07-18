//The file has the wrong name - Do not change it because it will mess everything up
//Just please leave it
//I beg
//PLEASE
//(Real reason is because itss funny xx)
float calculateAverage(float arr[]) {
  int sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += arr[i];
  }
  return (float)sum / 10;
} 

void readSensor(){
  DHT_Read();
  SkinTemp_Read();

  if (dhterror == false){
    if (DHTTempAV <= temperature_ref - 4){
      high_heat = true;
      HighHeat();
    }
    if (high_heat == true){ //No PID - only check temp to see if it is below 37 
    //Turn off high heat ...
      if(DHTTempAV > temperature_ref - 0.5){ //Once we reach the desired operating temp, go back to PID control
      high_heat = false; 
      digitalWrite(padHeat,LOW);
      Serial.println("Updating PID and Display");
      PID_control();
      }
      
    else{
      Serial.println("Updating PID and Display");
      PID_control();
    }
    error_counter = 0; //Set the successive error count to 0
    }
  }
  else{
    error_counter = error_counter + 1;
    dhterror = false;
    if (error_counter >= 5){ //If the error has occured 5 or more times in a row, display an error.
      display_error();
    }
  }
}

float* getDHTTempArray(int counter) { //Switch case to get the pointer to point at the correct DHT array
  switch (counter) {
    case 14:
      return DHT1temp;
    case 15:
      return DHT2temp;
    case 16:
      return DHT3temp;
    case 17:
      return DHT4temp;
    case 18:
      return DHT5temp;
    default:
      return NULL;
  }
}
float* getDHTHumidityArray(int counter) { //Switch case to get the pointer to point at the correct DHT array
  switch (counter) {
    case 14:
      return DHT1humidity;
    case 15:
      return DHT2humidity;
    case 16:
      return DHT3humidity;
    case 17:
      return DHT4humidity;
    case 18:
      return DHT5humidity;
    default:
      return NULL;
  }
}

void DHT_Read(){
sensors_event_t event;
// Get temperature event and print its value if there is no error. //Need to add the list it appends to :)
for (int counter = 14; counter < 19; counter++) { //14 15 16 17 18

  DHT_Unified dht(counter, DHTTYPE);
  dht.begin();
  dht.temperature().getEvent(&event); 
  float* dhtTempArray = getDHTTempArray(counter); //Set the dhtTempArray pointer to the right Temperature DHT array
  float* dhtHumidityArray = getDHTHumidityArray(counter); //Set the dhtHumidityArray pointer to the right Humidity array
  /*Serial.print(("DHT")); //Printing for debugging
  Serial.print((counter - 13)); */
    if (isnan(event.temperature) | temperature <= 0) {
      //Serial.println(F("Error reading temperature!"));
      dhterror = true; //Set error bool
    }
    else {
      int count = dhtTempArray[10];
      temperature = event.temperature; //Update temperature variable
      dhtTempArray[count] = temperature;
      dhtTempArray[10]=dhtTempArray[10]+1;
      if(dhtTempArray[10] == 10){
        dhtTempArray[10]=0;
      }
      /*Serial.print("      ");
      Serial.print(F("Temperature: "));
      Serial.print(temperature);
      Serial.println(F("°C")); */
    }
    // Get humidity event and print its value if there is no error.
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity) | humidity <= 0 | humidity > 100) {
      //Serial.println(F("Error reading humidity!"));
      dhterror = true;
    }
    else {
      int count = dhtHumidityArray[10];
      humidity = event.relative_humidity;
      dhtHumidityArray[count] = humidity ;
      dhtHumidityArray[10]=dhtHumidityArray[10]+1;
      if(dhtHumidityArray[10] == 10){
        dhtHumidityArray[10]=0;
      }

      /*Serial.print(F("Humidity: "));
      Serial.print(humidity);
      Serial.println(F("%"));
      Serial.print("HumTime: ");
      Serial.println(Time); */
    } 
  }
DHTTempAV =  calculateAverage(DHT1temp) + calculateAverage(DHT2temp) + calculateAverage(DHT3temp)+calculateAverage(DHT4temp) +calculateAverage(DHT5temp);
DHTHumAV = calculateAverage(DHT1humidity)+calculateAverage(DHT2humidity)+calculateAverage(DHT3humidity)+calculateAverage(DHT4humidity)+calculateAverage(DHT5humidity);
}

void SkinTemp_Read(){
  // Skin probe sensor reading
  skintempSensor.requestTemperatures();
  skin_temperature = skintempSensor.getTempC(thermometerAddress);
  if (skin_temperature < -100){ //If we ever get below -100 degrees in reality the incubator is not the problem to concern ourselves with. 
    display_dsberror();
  }
  else{
      int count = Skintemp[10];
      Skintemp[count] = skin_temperature ;
      Skintemp[10] = Skintemp[10] + 1;
      if (Skintemp[10] == 10){
        Skintemp[10] = 0;
      }
    }
  

}
  /*Serial.print("Skin temperature"); //Serial prints for debugging
  Serial.print(skin_temperature);
  Serial.print("°");
  Serial.println("C  ");*/

void oximeter(){
  pox.update();
  int count = heartbeat[10];
  heartbeat[count] = pox.getHeartRate() ;
  spo2[count]= pox.getSpO2();
  heartbeat[10] = heartbeat[10] + 1;
  if (heartbeat[10] == 10){
    heartbeat[10] = 0;
  }
heartbeatav = calculateAverage(heartbeat);
spo2av = calculateAverage(spo2);

}
