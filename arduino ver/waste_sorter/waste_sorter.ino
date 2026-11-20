// Smart Waste Segregator - two servo lifts controlled from the webcam page.
// The page sends "L1\n" to lift lift 1 and "L2\n" to lift lift 2 (9600 baud).
//
// Wiring (each servo): signal -> pin below, power -> external 5V supply,
// ground -> supply ground AND Arduino GND (common ground).

#include <Servo.h>

const int SERVO1_PIN = 3;
const int SERVO2_PIN = 4;

const int REST_ANGLE = 0;          // lowered position
const int LIFT_ANGLE = 90;         // raised position
const unsigned long HOLD_MS = 3000; // how long a lift stays up
const int STEP_DELAY_MS = 10;      // smaller = faster movement

Servo servo1;
Servo servo2;

void setup() {
  Serial.begin(9600);
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo1.write(REST_ANGLE);
  servo2.write(REST_ANGLE);
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd == "L1") {
      liftAndLower(servo1, 1);
    } else if (cmd == "L2") {
      liftAndLower(servo2, 2);
    }
  }
}

// Raise the servo smoothly, hold, then lower it smoothly
void liftAndLower(Servo &s, int number) {
  for (int a = REST_ANGLE; a <= LIFT_ANGLE; a++) {
    s.write(a);
    delay(STEP_DELAY_MS);
  }
  delay(HOLD_MS);
  for (int a = LIFT_ANGLE; a >= REST_ANGLE; a--) {
    s.write(a);
    delay(STEP_DELAY_MS);
  }
  Serial.print("Lift ");
  Serial.print(number);
  Serial.println(" done");
}
