/* //Bang-bang method :(
// Basic temp control - Test vs PID <- choose better
void temp_control(){
if (temperature < temperature_ref - 0.25){
  heat();
}
else if(temperature > temperature_ref + 0.25 ){
cool();
}
else{}
}
void heat(){
  //Turn relays on the correct way
}
void cool(){
  //Turn relays on the right way
}
*/

//PID CONTROLLER
void PID_control(){
  //const double output = myPID.Run(temperature);
  //analogWrite(TEMP_PID, output);

  //Calculate the error between the temp ref and the real value
  PID_error = temperature_ref - temperature;
  //Calculate the P value
  PID_p = kp * PID_error;
  //Calculate the I value in a range on +-3
  if(-3 < PID_error < 3){
    PID_i = PID_i + (ki * PID_error);//Should add a dt term
  }
  
  //For derivative we need real time to calculate speed change rate
  timePrev = Time;                            // the previous time is stored before the actual time read
  Time = millis();                            // actual time read
  elapsedTime = (Time - timePrev) / 1000; 
  //Now we can calculate the D calue
  PID_d = kd*((PID_error - previous_error)/elapsedTime);
  //Final total PID value is the sum of P + I + D
  PID_value = PID_p + PID_i + PID_d;

  //We define PWM range between 0 and 255
  if(PID_value < 0){
    PID_value = -1*PID_value;
    if (PID_value > 255){
    PID_value = 255;}
    cool();
  }
  if(PID_value > 0){
    if (PID_value > 255){
    PID_value = 255;}
    heat();
  }
  //Now we can write the PWM signal to the mosfet on digital pin D3
  //Since we activate the MOSFET with a 0 to the base of the BJT, we write 255-PID value (inverted)
  analogWrite(TEMP_PID,PID_value);
  previous_error = PID_error;     //Remember to store the previous error for next loop.     // print pid val

//   if (steady_state_temp = true) {
//     if (abs(PID_error) >= 3) {
//       printSensors.pause();   // pause the ticker
//       // set off alarm
//       digitalWrite()// turn off peltier
//       // keep fans on
//     }
//   }

 }

void heat(){
  digitalWrite(thermoregulation, LOW);
  digitalWrite(cooling, LOW);
  digitalWrite(heating, HIGH);

  // display.print("Heating ")
}

void cool(){
  digitalWrite(thermoregulation, HIGH);
  digitalWrite(heating, LOW); 
  digitalWrite(cooling, HIGH);
}




