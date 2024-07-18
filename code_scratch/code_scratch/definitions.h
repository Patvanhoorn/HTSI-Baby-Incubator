
#define padHeat 2     // Turns on the heating pads
#define TEMP_PID 3    // control mosfet voltage
#define fans 4        // relay 5, always on during heating or cooling
#define heating 5     // relay 1  //Determines peltier connections polarity
#define cooling 6     // relay 2  //Reverses peltier connections
#define thermoregulation 7 // relay 3
#define humidifier 8  // relay 4
const int DATA_PIN = 9;  // Pin 9 of Arduino Uno (connected to SER pin of 74HC595)  Data Pin   Register Pin 14
const int CLOCK_PIN = 10;  // Pin 10 of Arduino Uno (connected to SRCLK pin of 74HC595)  Clock Pin  Register Pin 11
const int LATCH_PIN = 11;  // Pin 11 of Arduino Uno (connected to RCLK pin of 74HC595) Latch Pin Register Pin 12
#define ONE_WIRE_BUS 12    // DS18B20 data wire is connected to input 12
#define waterlevel 13  // always on

#define DHTTYPE    DHT22
int DHTPIN = 15;
// #define DHTPIN1 14 DHTS attached from A0 to A
// #define DHTPIN2 15
// #define DHTPIN3 16
// #define DHTPIN4 17
// #define DHTPIN5 18

float DHT1temp[11] = {-10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0,0}; //Last value in array is the counter number for the average. On setup, edit it 10 times
float DHT2temp[11] = {-10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0,0};
float DHT3temp[11] = {-10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0,0};
float DHT4temp[11] = {-10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0,0};
float DHT5temp[11] = {-10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0,0};

int DHT1humidity[11] = {50, 50, 50, 50, 50, 50, 50, 50, 50, 50,0}; //Saves space but having ints rather than floats
int DHT2humidity[11] = {50, 50, 50, 50, 50, 50, 50, 50, 50, 50,0};
int DHT3humidity[11] = {50, 50, 50, 50, 50, 50, 50, 50, 50, 50,0};
int DHT4humidity[11] = {50, 50, 50, 50, 50, 50, 50, 50, 50, 50,0};
int DHT5humidity[11] = {50, 50, 50, 50, 50, 50, 50, 50, 50, 50,0};

float heartbeat[11] = {0,0,0,0,0,0,0,0,0,0,0};
float spo2[11]= {0,0,0,0,0,0,0,0,0,0,0};
float heartbeatav;
float spo2av;


float DHTTempAV;
int DHTHumAV;

float Skintemp[11] = {-10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0,0};

// Oled display size
#define OLED_RESET  -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels




bool ds18b20error = false;
bool dhterror = false; //Boolean check for whether data was read correctly or not
int error_counter=0; //To count to sucessive errors of readings if it occurs
int skin_error_counter=0;


int humidity;
float temperature;
float skin_temperature;

float air_temp_ref; //Temperature of the air based of the skin temp and reference temperature of the baby
float offset_temp = 0.0; //Based on the babies age, the internal air will need to be offset from that babies skin temperature
float temperature_ref = 37.0; // reference temp - the ideal temperature both baby and air would be at given an offset
int humidity_ref = 75;

int temp_cases;
bool steady_state_temp = false;

bool humidifying = false; //Is the humidifier on and going to the other extreme
bool high_heat = false;   //More powerful heaters
bool heater = false; //Peltier Heat
bool cooler = false; //Peliter cool

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

//Sensor Functions Declaration
float calculateAverage(float arr[]);
int calculateAverage2(int arr[]);
void readSensor();
void DHT_Read();
void SkinTemp_Read();
void oximeter();
//Temp Control 
void PID_control();
void heat();
void cool();
void HighHeat();
void humidityControl();
//Display Update
void display_update();
void display_DHTerror();
void display_dsberror();
void display_tempcheck();
void display_skintempcheck();
void display_humdidtyerror();
void display_heartcheck();
void display_o2check();
void display_roomTemp();
void register_update();
