//PID CONTROLLER
void PID_control(){
  PID_error = temperature_ref - temperature; //Calculate the error between the temp ref and the real value
  PID_p = kp * PID_error; //Calculate the P value
  if(-3 < PID_error < 3){ //Calculate the I value in a range on +-3
    PID_i = PID_i + (ki * PID_error);//Can add a dt term and close 
  }
  timePrev = Time; // the previous time is stored before the actual time read
  Time = millis(); // actual time read
  elapsedTime = (Time - timePrev) / 1000;
  PID_d = kd*((PID_error - previous_error)/elapsedTime); //Calculate the D calue
  PID_value = PID_p + PID_i + PID_d; //Final total PID value is the sum of P + I + D


  if(PID_value < 0){
    PID_value = -1*PID_value;
    if (PID_value > 255){ //Saturated the PID
    PID_value = 255;}
    cool();
  }
  else {
    if (PID_value > 255){
    PID_value = 255;}
    heat();
  }
  //Now we can write the PWM signal to the mosfet on digital pin D3
  analogWrite(TEMP_PID,PID_value);
  previous_error = PID_error;  //Remember to store the previous error for next loop.

  display.print("Error: ");
  display.println(PID_error);
  display.print("Analog value: ");
  display.println(PID_value);
}

void heat(){
  digitalWrite(thermoregulation, LOW);
  digitalWrite(cooling, LOW);
  digitalWrite(heating, HIGH);
  display.println("Heating ON");
}

void cool(){
  digitalWrite(thermoregulation, HIGH);
  digitalWrite(heating, LOW); 
  digitalWrite(cooling, HIGH);
  display.println("Cooling ON");

}






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


