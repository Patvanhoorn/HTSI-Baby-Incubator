//The file has the wrong name - Do not change it because it will mess everything up
//Just please leave it
//I beg
//PLEASE
//(Real reason is because itss funny xx)
float calculateAverage(float arr[]) { //For floats
  float sum = 0;
  for (int i = 0; i < 10; i++) {
   //Serial.println(sum);
    sum += arr[i];
  //  Serial.println(arr[i]);
    
  }
 // Serial.print(F("Sum"));
  //Serial.println(sum/10);
  return sum / 10;
} 

int calculateAverage2(int arr[]) { //For ints
  float sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += arr[i];
  }
  return sum / 10;
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
      //Serial.println(F("Updating PID and Display"));
      PID_control();
      }
      
    else{
      //Serial.println(F("Updating PID and Display"));
      PID_control();
    }
    error_counter = 0; //Set the successive error count to 0
    }
  }
  else{
    error_counter = error_counter + 1;
    dhterror = false;
    }
  }


/*void DHT_Read(){
// Get temperature event and print its value if there is no error. //Need to add the list it appends to :)
for (int pin_number = 22; pin_number < 25; pin_number++) { //22 23 24 25 
  int temp_pin_number = pin_number;
  DHT_Unified dht(temp_pin_number, DHTTYPE);
  dht.begin();
  Serial.print("Pin:  ");
  Serial.println(temp_pin_number);
  sensors_event_t event;
  dht.temperature().getEvent(&event); 
  dht.humidity().getEvent(&event);

  float* dhtTempArray = getDHTTempArray(temp_pin_number); //Set the dhtTempArray pointer to the right Temperature DHT array
  int* dhtHumidityArray = getDHTHumidityArray(temp_pin_number); //Set the dhtHumidityArray pointer to the right Humidity array 
    if (isnan(event.temperature)) {
      Serial.println(F("Error reading temperature!"));
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
      Serial.print(F("Temperature: "));
      Serial.print(temperature);
      Serial.println(F("°C")); 
    }
    // Get humidity event and print its value if there is no error.
    if (isnan(event.relative_humidity)) {
      Serial.println(F("Error reading humidity!"));
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

      Serial.print(F("Humidity: "));
      Serial.print(humidity);
      Serial.println(F("%"));
    } 
  }
DHTTempAV =  ((calculateAverage(DHT1temp) + calculateAverage(DHT2temp) + calculateAverage(DHT3temp)+calculateAverage(DHT4temp))/4);
DHTHumAV = ((calculateAverage2(DHT1humidity)+calculateAverage2(DHT2humidity)+calculateAverage2(DHT3humidity)+calculateAverage2(DHT4humidity))/4);
}
*/
void DHT_Read() {
  // Delay between measurements.
  int time_start = millis();
  // Get temperature event and print its value.
  sensors_event_t event;
  sensors_event_t event2;
  sensors_event_t event3;
  sensors_event_t event4;
  
  dht.temperature().getEvent(&event);
  dht2.temperature().getEvent(&event2);
  dht3.temperature().getEvent(&event3);
  dht4.temperature().getEvent(&event4);


  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature 1!"));
    dhterror = true; //Set error bool
  }
  else {
    int count = DHT1temp[10];
    float temperature = event.temperature; //Update temperature variable
    DHT1temp[count] = temperature;
    DHT1temp[10]=DHT1temp[10]+1;
    if(DHT1temp[10] == 10){
        DHT1temp[10]=0;
      }
    // Serial.print(F("Temperature 1: "));
    // Serial.print(temperature);
    // Serial.println(F("°C")); 
  }
  if (isnan(event2.temperature)) {
    Serial.println(F("Error reading temperature 2!"));
    dhterror = true;
  }
  else {
    int count = DHT2temp[10];
    float temperature = event2.temperature; //Update temperature variable
    DHT2temp[count] = temperature;
    DHT2temp[10]=DHT2temp[10]+1;
    if(DHT2temp[10] == 10){
        DHT2temp[10]=0;
      }
    // Serial.print(F("Temperature 2: "));
    // Serial.print(temperature);
    // Serial.println(F("°C")); 
  }
  if (isnan(event3.temperature)) {
    Serial.println(F("Error reading temperature 3!"));
    dhterror = true;
  }
  else {
    int count = DHT3temp[10];
    float temperature = event3.temperature; //Update temperature variable
    DHT3temp[count] = temperature;
    DHT3temp[10]=DHT3temp[10]+1;
    if(DHT3temp[10] == 10){
        DHT3temp[10]=0;
      }
    // Serial.print(F("Temperature 3: "));
    // Serial.print(temperature);
    // Serial.println(F("°C")); 
  }
  if (isnan(event4.temperature)) {
    Serial.println(F("Error reading temperature 4!"));
    dhterror = true;
  }
  else {
    int count = DHT4temp[10];
    float temperature = event4.temperature; //Update temperature variable
    DHT4temp[count] = temperature;
    DHT4temp[10]=DHT4temp[10]+1;
    if(DHT4temp[10] == 10){
        DHT4temp[10]=0;
      }
    // Serial.print(F("Temperature 4: "));
    // Serial.print(temperature);
    // Serial.println(F("°C")); 
  }

  dht.humidity().getEvent(&event);
  dht2.humidity().getEvent(&event2);
  dht3.humidity().getEvent(&event3);
  dht4.humidity().getEvent(&event4);


  // Get humidity event and print its value.
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity 1!"));
  }
 else {
      int count = DHT1humidity[10];
      int humidity = event.relative_humidity;
      DHT1humidity[count] = humidity ;
      DHT1humidity[10]=DHT1humidity[10]+1;
      if(DHT1humidity[10] == 10){
        DHT1humidity[10]=0;
      }
      // Serial.print(F("Humidity 1  : "));
      // Serial.print(humidity);
      // Serial.println(F("%"));
    } 
  if (isnan(event2.relative_humidity)) {
    Serial.println(F("Error reading humidity 2!"));
  }
 else {
      int count = DHT2humidity[10];
      int humidity = event2.relative_humidity;
      DHT2humidity[count] = humidity ;
      DHT2humidity[10]=DHT2humidity[10]+1;
      if(DHT2humidity[10] == 10){
        DHT2humidity[10]=0;
      }
      // Serial.print(F("Humidity 2: "));
      // Serial.print(humidity);
      // Serial.println(F("%"));
    } 
  if (isnan(event3.relative_humidity)) {
    Serial.println(F("Error reading humidity 3!"));
  }
  else {
      int count = DHT3humidity[10];
      int humidity = event3.relative_humidity;
      DHT3humidity[count] = humidity ;
      DHT3humidity[10]=DHT3humidity[10]+1;
      if(DHT3humidity[10] == 10){
        DHT3humidity[10]=0;
      }
      // Serial.print(F("Humidity 3: "));
      // Serial.print(humidity);
      // Serial.println(F("%"));
    } 
  if (isnan(event4.relative_humidity)) {
    Serial.println(F("Error reading humidity 4!"));
  }
  else {
      int count = DHT4humidity[10];
      int humidity = event4.relative_humidity;
      DHT4humidity[count] = humidity ;
      DHT4humidity[10]=DHT4humidity[10]+1;
      if(DHT4humidity[10] == 10){
        DHT4humidity[10]=0;
      }
      // Serial.print(F("Humidity 4: "));
      // Serial.print(humidity);
      // Serial.println(F("%"));
    } 
  DHTTempAV =  ((calculateAverage(DHT1temp) + calculateAverage(DHT2temp) + calculateAverage(DHT3temp)+calculateAverage(DHT4temp))/4);
  DHTHumAV = ((calculateAverage2(DHT1humidity)+calculateAverage2(DHT2humidity)+calculateAverage2(DHT3humidity)+calculateAverage2(DHT4humidity))/4);

  // Serial.print(F("Average temp "));
  // Serial.println(DHTTempAV);
  // Serial.print(F("Average humidity "));
  // Serial.println(DHTHumAV);
  int time_end = millis();
  Serial.print("Time per read:  ");
  Serial.println(time_end-time_start);
}


void SkinTemp_Read(){
  skintempSensor.requestTemperatures();   // Skin probe sensor reading
  skin_temperature = skintempSensor.getTempC(thermometerAddress);
  if (skin_temperature < -100){ //If we ever get below -100 degrees in reality the incubator is not the problem to concern ourselves with. 
    skin_error_counter = skin_error_counter + 1;
    
  }
  else{
      //Serial.println(skin_temperature);
      int count = Skintemp[10];
      skin_error_counter = 0;
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
/*  heartbeat[count] = pox.getHeartRate() ;
  Serial.print(F("Heartbeat"));
  Serial.println(pox.getHeartRate());
  spo2[count]= pox.getSpO2();
  heartbeat[10] = heartbeat[10] + 1;
  if (heartbeat[10] == 10){
    heartbeat[10] = 0;
  }
heartbeatav = calculateAverage(heartbeat);
spo2av = calculateAverage(spo2);
Serial.print(F("Heartbeat:  "));
Serial.println(heartbeatav);
Serial.print(F("Spo2:  "));
Serial.println(spo2av);*/
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate:");
        Serial.print(pox.getHeartRate());
        Serial.print("bpm / SpO2:");
        Serial.print(pox.getSpO2());
        Serial.println("%");

        tsLastReport = millis();
    }
}
