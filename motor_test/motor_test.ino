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

void setup() {
  Motor1.begin(M1_PWM, M1_INA, M1_INB);    // Motor 1 object connected through specified pins 
  Motor2.begin(M2_PWM, M2_INA, M2_INB);    // Motor 1 object connected through specified pins 
  Serial.begin(115200);   
}

void loop() {
  // forward
  Motor1.setSpeed(300); // motor 3/4-speed "forward"
  Motor2.setSpeed(300); // motor 3/4-speed "forward"
  delay(2000); // wait for 2 seconds

  Motor1.setSpeed(0); // motor stop (coasting)
  Motor2.setSpeed(0); // motor stop (coasting)
  delay(2000); // wait for 2 seconds
  

  // backward
  Motor1.setSpeed(-300); // motor 3/4-speed "forward"
  Motor2.setSpeed(-300); // motor 3/4-speed "forward"
  delay(2000); // wait for 2 seconds

  Motor1.setSpeed(0); // motor stop (coasting)
  Motor2.setSpeed(0); // motor stop (coasting)
  delay(2000); // wait for 2 seconds

  // turn left
  Motor1.setSpeed(300); // motor 3/4-speed "forward"
  Motor2.setSpeed(-300); // motor 3/4-speed "forward"
  delay(2000); // wait for 2 seconds

  Motor1.setSpeed(0); // motor stop (coasting)
  Motor2.setSpeed(0); // motor stop (coasting)
  delay(2000); // wait for 2 seconds

  // turn right
  Motor1.setSpeed(-300); // motor 3/4-speed "forward"
  Motor2.setSpeed(300); // motor 3/4-speed "forward"
  delay(2000); // wait for 2 seconds

  Motor1.setSpeed(0); // motor stop (coasting)
  Motor2.setSpeed(0); // motor stop (coasting)
  delay(2000); // wait for 2 seconds
}
