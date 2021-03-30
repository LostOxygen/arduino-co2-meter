//Pin variables for LEDs and the sensor
int SensorPin = 5;
int RED=6; 
int YELLOW=7;  
int GREEN=8;  

int MeasureRange = 5000;
unsigned long TimeMicroSecs; 
unsigned long TimeMilliSecs; 

int PPM = 0; //PPM Measurement
float Percentage = 0;


void setup() {
  //Define In- and Output Pins
  pinMode(SensorPin, INPUT);  
  pinMode(RED, OUTPUT); 
  pinMode(YELLOW, OUTPUT); 
  pinMode(GREEN,OUTPUT); 
  //start serial connection 
  Serial.begin(9600);
}

void loop() {
  TimeMicroSecs = pulseIn(SensorPin, HIGH, 2000000); // get PWM signal
  TimeMilliSecs = TimeMicroSecs/1000; // convert microsecs in millisecs
  float Percantage = TimeMilliSecs / 1004.0; // percantage indicates the ppm value as the pwm signal length over the available measurerange
  PPM = MeasureRange * Percentage; // calculate the ppm value
  Serial.print("CO2 stake in PPM: ");
  Serial.println(PPM);
  //refresh the leds and wait for 1000millisecs
  SetLedColor();
  delay(1000);
}

void SetLedColor() {
  if (PPM < 800){
    digitalWrite(GREEN, HIGH);
    digitalWrite(YELLOW, LOW);
    digitalWrite(RED, LOW); 
  }
  else if (PPM > 800 && PPM < 1200){
    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, HIGH);
    digitalWrite(RED, LOW);
  }
  else if (PPM > 1200){
    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(RED, HIGH);
  }
}
