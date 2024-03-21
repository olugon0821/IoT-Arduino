enum PINS{
  JOYSTICK = A1,
  SERVO = 13

};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200UL);
  pinMode(JOYSTICK, INPUT);
  pinMode(SERVO, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t x_value {analogRead(JOYSTICK)};
  Serial.print(F("X value : "));
  uint16_t mapped_value {map(x_value,0,1023,0,255)};
  Serial.println(mapped_value);
  analogWrite(SERVO, mapped_value);
  delay(50UL);

}
