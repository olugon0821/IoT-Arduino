#include <Stepper.h>
const uint16_t STEP_REVOLUTION {2048U}; // 32 * 64 = 360
class Stepper stepping(STEP_REVOLUTION,42,43,44,45);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200UL);
  stepping.setSpeed(14); // rpm 14

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(F("Clockwise"));
  stepping.step(STEP_REVOLUTION);

  Serial.println(F("Counter Clockwise"));
  stepping.step(-STEP_REVOLUTION);
}
