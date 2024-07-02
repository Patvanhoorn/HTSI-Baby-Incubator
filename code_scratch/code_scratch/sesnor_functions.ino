void sensor_read(){
  result = dht11.readTemperatureHumidity(temperature, humidity); //Read values
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
    }
}