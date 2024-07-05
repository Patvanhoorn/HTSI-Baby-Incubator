#define DHTPIN 2 
#define TEMP_PID 3    // control mosfet voltage
#define fans 4        // relay 5, always on during heating or cooling
#define heating 5     // relay 1
#define cooling 6     // relay 2
#define thermoregulation 7 // relay 3
#define humidifier 8  // relay 4
// DHT11 pin 12
#define DHTTYPE    DHT22  //Pin 2
#define moisture_sensor 13  // always on



// Oled display size
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


bool dhterror = false;
int humidity;
float temperature;
int result;
float temperature_ref = 37; // reference temp
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


//void temp_control();
void heat();
void cool();
void PID_control();


void readSensor();