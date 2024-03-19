const uint8_t SWITCH_PIN {40U};
const uint8_t LED_PIN {42U};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200UL); // 시리얼 통신 - 모니터에 값 출력
  pinMode(LED_PIN, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  bool SW_state = digitalRead(SWITCH_PIN); // True = HIGH, False = LOW
  if (SW_state){
    Serial.println(F("SW ON"));
    digitalWrite(LED_PIN,HIGH);
  }else{
    Serial.println(F("SW OFF"));
    digitalWrite(LED_PIN, LOW);
  }
  delay(100UL);
}
