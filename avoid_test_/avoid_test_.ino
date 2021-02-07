#include <VNH3SP30.h>

VNH3SP30 Motor1;    // define control object for 1 motor
VNH3SP30 Motor2;    // define control object for 1 motor

// motor pins
#define M1_INA 2    // control pin INA (digital output)
#define M1_PWM 3    // pwm pin motor (digital output)
#define M1_INB 4    // control pin INB (digital output)

#define M2_INA 10   // control pin INA (digital output)
#define M2_PWM 11   // pwm pin motor (digital output)
#define M2_INB 12   // control pin INB (digital output)

int trig_L = 5;    // TRIG pin
int trig_M = 6;
int trig_R = 7;

int echo_L = 8;    // ECHO pin
int echo_M = 9; 
int echo_R = 13;

int wall = 50; // distance threshold

float dist_L, dist_M, dist_R;

// implemented from https://github.com/UMD-ENEE408I/ENEE408I_Fall_2020/blob/team1/arduino/arduino.ino //
// may need to tune this to work with our stuff //

void getSensorL(){
  digitalWrite(trig_L, HIGH);
  delayMicroseconds(60);
  digitalWrite(trig_L, LOW);
  dist_L = pulseIn(echo_L, HIGH) * 0.017;
}

void getSensorM(){
  digitalWrite(trig_M, HIGH);
  delayMicroseconds(60);
  digitalWrite(trig_M, LOW);
  dist_M = pulseIn(echo_M, HIGH) * 0.017;
}

void getSensorR(){
  digitalWrite(trig_R, HIGH);
  delayMicroseconds(60);
  digitalWrite(trig_R, LOW);
  dist_R = pulseIn(echo_R, HIGH) * 0.017;
}

void getAllSensors(){
  getSensorL();
  getSensorM();
  getSensorR();
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
  delay(500);
  stopAll();
}

void left(){
  Motor1.setSpeed(100); // motor 1/4-speed "forward"
  Motor2.setSpeed(-100); // motor 1/4-speed "forward"
  delay(500);
  stopAll();
}


bool checkWall(){
  if(dist_L<wall || dist_M<wall || dist_R<wall){
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
  while(!Serial.available()){
    getAllSensors();
    forward();
    if(checkWall()){
      stopAll();
      delay(100);
      backward();
      delay(100);
      chooseDir();
    }
  }
}
