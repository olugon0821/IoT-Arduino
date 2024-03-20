const uint8_t SWITCH_PIN {40U};
const uint8_t LED_PIN {42U};
const uint8_t BUZZ_PIN {44U};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200UL); // 시리얼 통신 - 모니터에 값 출력
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZ_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:
  bool SW_state = digitalRead(SWITCH_PIN); // True = HIGH, False = LOW
  if (SW_state ){
    Serial.println(F("SW ON"));
    digitalWrite(LED_PIN,HIGH);
    tone(BUZZ_PIN,100);
  }else{
    Serial.println(F("SW OFF"));
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZ_PIN);
  }
  delay(100UL);
}
