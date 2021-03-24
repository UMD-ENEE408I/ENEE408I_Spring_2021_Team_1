#include <VNH3SP30.h>

VNH3SP30 Motor1;    // define control object for 1 motor
VNH3SP30 Motor2;    // define control object for 1 motor

// motor pins
#define M1_INA 4    // control pin INA (digital output)
#define M1_PWM 3    // pwm pin motor (digital output)
#define M1_INB 2    // control pin INB (digital output)

#define M2_INA 10   // control pin INA (digital output)
#define M2_PWM 11   // pwm pin motor (digital output)
#define M2_INB 12   // control pin INB (digital output)

int echo_L = 5;    // ECHO pin
int echo_M = 6; 
int echo_R = 7;

int trig_L = 8;    // TRIG pin
int trig_M = 9;
int trig_R = 13;

int wall = 50; // distance threshold

float dist_L, dist_M, dist_R;

int getSensor(int echo, int trig){
  int dist;
  digitalWrite(trig, HIGH);
  delayMicroseconds(60);
  digitalWrite(trig, LOW);
  return dist = pulseIn(echo, HIGH) * 0.017;
}


void getAllSensors(){
  dist_L = getSensor(echo_L, trig_L);
  dist_M = getSensor(echo_M, trig_M);
  dist_R = getSensor(echo_R, trig_R);
}

void forward(){
  Motor1.setSpeed(100); // motor 1/4-speed "forward"
  Motor2.setSpeed(100); // motor 1/4-speed "forward"
}

void backward(){
  Motor1.setSpeed(-100); // motor 1/4-speed "forward"
  Motor2.setSpeed(-100); // motor 1/4-speed "forward"
}

void stopAll(){
  Motor1.setSpeed(0); // motor stop (coasting)
  Motor2.setSpeed(0); // motor stop (coasting)
}

void right(){
  Motor1.setSpeed(-100); // motor 1/4-speed "forward"
  Motor2.setSpeed(100); // motor 1/4-speed "forward"
  delay(700);
  stopAll();
}

void left(){
  Motor1.setSpeed(100); // motor 1/4-speed "forward"
  Motor2.setSpeed(-100); // motor 1/4-speed "forward"
  delay(700);
  stopAll();
}


bool checkWall(){
  if(dist_L < wall || dist_M < wall || dist_R < wall){
    return true;
  }
  return false;
}

void chooseDir(){
  if(dist_L>dist_R){
    left();
  }
  else{
    right();
  }
}

void setup() {
  Serial.begin(9600); 
    
  // initialize motors
  Motor1.begin(M1_PWM, M1_INA, M1_INB,-1,-1);    // Motor 1 object connected through specified pins 
  Motor2.begin(M2_PWM, M2_INA, M2_INB,-1,-1);    // Motor 1 object connected through specified pins 

  // initialize ultrasonic
  pinMode(trig_L, OUTPUT);
  pinMode(trig_M, OUTPUT);
  pinMode(trig_R, OUTPUT);

  pinMode(echo_L, INPUT);
  pinMode(echo_M, INPUT);
  pinMode(echo_R, INPUT);
}

void loop() {
    getAllSensors();
    if(checkWall()){
      stopAll();
      delay(100);
      backward();
      delay(100);
      chooseDir();
    } else { 
    forward();
    } 
}
