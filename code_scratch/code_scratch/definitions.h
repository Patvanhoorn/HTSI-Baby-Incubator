#define TEMP_PID 3    // control mosfet voltage
#define fans 4        // always on during heating or cooling
#define heating 5     // first relay
#define cooling 6     // second relay
#define thermoregulation 7 // third relay
#define humidifier 8  // fourth relay
// DHT11 pin 12
#define moisture_sensor 13  // always on


int humidity;
int temperature;
int result;
int temperature_ref = 37; // reference temp
int humidity_ref = 75;
int temp_cases;
bool steady_state_temp = false;
bool steady_state_humidity = false;

//For PID
int kp = 2, ki = 5, kd = 1; 

float PID_error = 0;
float previous_error = 0;
float elapsedTime, Time, timePrev;
float PID_value = 0;

int PID_p = 0;    int PID_i = 0;    int PID_d = 0;
float last_kp = 0;
float last_ki = 0;
float last_kd = 0;
int PID_values_fixed =0;


void temp_control();
void heat();
void cool();
void PID_control();


void sensor_read();