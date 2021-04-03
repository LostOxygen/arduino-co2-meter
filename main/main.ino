//Pin variables for LEDs and the sensor
#define SENSORPIN D0
#define RED D6
#define YELLOW D7 
#define GREEN D8  

float MeasureRange = 5000;
unsigned long TimeMicroSecs; 
unsigned long TimeMilliSecs; 
const int WaitTime = 100;

float PPM = 0; //PPM Measurement
float Percentage = 0;


void setup() {
  //Define In- and Output Pins
  pinMode(SENSORPIN, INPUT);  
  pinMode(RED, OUTPUT); 
  pinMode(YELLOW, OUTPUT); 
  pinMode(GREEN,OUTPUT); 
  //start serial connection 
  Serial.begin(115200);
}

void loop() {
  TimeMicroSecs = pulseIn(SENSORPIN, HIGH, 1004000); // get PWM signal
  TimeMilliSecs = TimeMicroSecs/1000; // convert microsecs in millisecs
  Percentage = TimeMilliSecs / 1004.0; // percantage indicates the ppm value as the pwm signal length over the available measurerange
  Serial.print("Percantage: ");
  Serial.println(Percentage);
  PPM = MeasureRange * Percentage; // calculate the ppm value
  Serial.print("CO2 stake in PPM: ");
  Serial.println(PPM);
  //refresh the leds and wait for 1000millisecs
  SetLedColor(PPM);
  delay(WaitTime);
}

void SetLedColor(float PPM) {
  if (PPM < 800){
    digitalWrite(GREEN, HIGH);
    digitalWrite(YELLOW, LOW);
    digitalWrite(RED, LOW); 
  }
  else if (PPM > 700 && PPM < 1100){
    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, HIGH);
    digitalWrite(RED, LOW);
  }
  else if (PPM > 1100){
    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(RED, HIGH);
  }
}
