const uint8_t DS_PIN = {13U};
const uint8_t LATCH_PIN = {12U};
const uint8_t CLOCK_PIN = {11U};

void setup() {
  // put your setup code here, to run once:
  pinMode(DS_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  // -LATCH를 이용해 걸기
  digitalWrite(LATCH_PIN,LOW); // 잠그기
  shiftOut(DS_PIN, CLOCK_PIN, MSBFIRST, B10101010);
  digitalWrite(LATCH_PIN, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:

}
