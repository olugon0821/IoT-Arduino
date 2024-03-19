const uint8_t DS_PIN = {13U};
const uint8_t LATCH_PIN = {12U};
const uint8_t CLOCK_PIN = {11U};
const uint8_t LIGHT_PIN {A1};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(DS_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LIGHT_PIN, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t light_value {analogRead(LIGHT_PIN)};
  Serial.println(light_value);
  uint16_t lightV {map(light_value,200,600,0,255)};
  digitalWrite(LATCH_PIN,LOW);
  shiftOut(DS_PIN, CLOCK_PIN, MSBFIRST, lightV);
  digitalWrite(LATCH_PIN, HIGH);
  delay(500UL);
}
