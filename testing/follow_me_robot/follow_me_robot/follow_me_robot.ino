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

int echo_M = 6; 
int trig_M = 9;

void setup()
{
  Serial.begin(9600); 
    
  // initialize motors
  Motor1.begin(M1_PWM, M1_INA, M1_INB,-1,-1);    // Motor 1 object connected through specified pins 
  Motor2.begin(M2_PWM, M2_INA, M2_INB,-1,-1);
  
  pinMode(M1_INA,OUTPUT);
  pinMode(M1_PWM,OUTPUT);
  pinMode(M1_INB,OUTPUT);
  pinMode(M2_INA,OUTPUT);
  pinMode(M2_PWM,OUTPUT);
  pinMode(M2_INB,OUTPUT);
  
  pinMode(trig_M,OUTPUT);
  pinMode(echo_M,INPUT);
}
void loop()
{
  int duration,distance;
  digitalWrite(trig_M,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig_M,LOW);
  duration=pulseIn(echo_M,HIGH);
  distance=(duration/2)/29.1;
  if(distance>=40)
  {
    stopAll();
    delay(500);
  }
 else
  {
    if(distance>=25)
    {
    backward();
    delay(400);
  }
  else
 {
    forward();
    delay(400);
  }
 }
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
