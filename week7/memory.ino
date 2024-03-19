const uint8_t DS_PIN = {13U};
const uint8_t LATCH_PIN = {12U};
const uint8_t CLOCK_PIN = {11U};
const uint8_t VR_PIN {A0};

void setup() {
  // put your setup code here, to run once:
  pinMode(DS_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  // -LATCH를 이용해 걸기
  pinMode(VR_PIN,INPUT);
  Serial.begin(115200UL);
}

void loop() {
  // put your main code here, to run repeatedly:
  // uint16_t vr_value {analogRead(VR_PIN)};
  // uint16_t mapped_value {map(vr_value,0,1023,0,255)};
if (Serial.available()){
  int input_value {Serial.parseInt()};
  digitalWrite(LATCH_PIN,LOW); // 잠그기
  shiftOut(DS_PIN, CLOCK_PIN, MSBFIRST, input_value);
  digitalWrite(LATCH_PIN, HIGH);
  }
}
