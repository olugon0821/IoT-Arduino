const uint8_t SW {12U};

void setup() {
  // put your setup code here, to run once:
  pinMode(SW,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(SW, HIGH);
  delay(1000UL);
  digitalWrite(SW, LOW);
  delay(1000UL);
}
