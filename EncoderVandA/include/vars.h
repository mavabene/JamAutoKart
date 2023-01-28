
bool init1;
// timeStamp
//int last_freq = 0;
//unsigned long currentMillis = 0;
unsigned long currentMillis = 0;
unsigned long startMillis = 0;

unsigned long sM = 0;
int ledState = LOW;
float Steering_pot_inputVal = 400;

int derivativeIdx =0;


// conversions
float deg_per_ms_TO_deg_per_sec = 1000;

//debug
float test_var = 30;
int *test_ptr;

//steering
float angle_dt = 20; // in milliseconds
int idxSteeringV = 0;
float dSumSteeringV = 0;
float dMeanSteeringV = 0;
float current_angle = 0;
float start_angle = 0;
float min_detectable_angle = -45;  // as measureable by encoder
float max_detectable_angle = 45;
float steering_angular_vel = 0;
unsigned long angle_detect_start_time = 0;
float last_angle = 0;
