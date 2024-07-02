#define heat_supply 8
#define fan1 9
#define fan2 10
#define humidifier 11
#define moisture_sensor 13
#define TEST_LED 2
#define TEMP_PID 3



int humidity;
int temperature;
int result;
int temperature_ref = 37;
int temp_cases;


void temp_control();
void heat();
void cool();
void PID_control();

double Kp = 2, Ki = 5, Kd = 1; //For PID



void sensor_read();