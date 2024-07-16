
#define DHT_PIN 2 
#define TEMP_PID 3    // control mosfet voltage
#define fans 4        // relay 5, always on during heating or cooling
#define heating 5     // relay 1
#define cooling 6     // relay 2
#define thermoregulation 7 // relay 3
#define humidifier 8  // relay 4
const int DATA_PIN = 9;  // Pin 9 of Arduino Uno (connected to SER pin of 74HC595)  Data Pin   Register Pin 14
const int CLOCK_PIN = 10;  // Pin 10 of Arduino Uno (connected to SRCLK pin of 74HC595)  Clock Pin  Register Pin 11
const int LATCH_PIN = 11;  // Pin 11 of Arduino Uno (connected to RCLK pin of 74HC595) Latch Pin Register Pin 12
#define ONE_WIRE_BUS 12    // DS18B20 data wire is connected to input 12
#define moisture_sensor 13  // always on



#define DHTTYPE    DHT22  //Pin 2


// Oled display size
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


#define OLED_RESET  -1 // Reset pin # (or -1 if sharing Arduino reset pin)



bool dhterror = false; //Boolean check for whether data was read correctly or not
int error_counter; //To count to sucessive errors of readings if it occurs
int humidity;
float temperature;
float skin_temperature;
int result;
float temperature_ref = 37; // reference temp
int humidity_ref = 75;
int temp_cases;
bool steady_state_temp = false;
bool steady_state_humidity = false;

bool heater = false;
bool cooler = false;

//For PID
int kp = 50, ki = 0, kd = 0;

float PID_error = 0;
float previous_error = 0;
float elapsedTime, Time, timePrev;
float PID_value = 0;

int PID_p = 0;    int PID_i = 0;    int PID_d = 0;
float last_kp = 0;
float last_ki = 0;
float last_kd = 0;
int PID_values_fixed =0;

//For register
byte leds = 0;


void heat();
void cool();
void PID_control();
void readSensor();
void display_error();
void display_update();
void register_update();