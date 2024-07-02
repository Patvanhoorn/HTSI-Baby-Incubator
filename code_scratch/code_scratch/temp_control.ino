// Basic temp control - Test vs PID
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
//PID CONTROLLER
