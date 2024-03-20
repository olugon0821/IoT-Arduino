const uint8_t EQ_PIN {40U};
const uint8_t SWITCH_PIN {42U};
const uint8_t BUZZ_PIN {44U};
const uint8_t DS_PIN {13U};
const uint8_t LATCH_PIN = {12U};
const uint8_t CLOCK_PIN = {11U};

int count {0};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200UL); // 시리얼 통신 - 모니터에 값 출력
  pinMode(SWITCH_PIN, INPUT);
  pinMode(BUZZ_PIN, OUTPUT);
  pinMode(EQ_PIN, INPUT_PULLUP);
  pinMode(DS_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool SW_state = digitalRead(EQ_PIN); 
  bool Reset = digitalRead(SWITCH_PIN);
  
  if(SW_state)
    count++;
    Serial.println(count);
    delay(100);

  if (count >= 1 && count <= 8) {
      uint8_t LED = (1 << count) - 1; 
      digitalWrite(LATCH_PIN, LOW);
      shiftOut(DS_PIN, CLOCK_PIN, MSBFIRST, LED);
      digitalWrite(LATCH_PIN, HIGH);
    }

  if (count >= 8){
    tone(BUZZ_PIN,200);
  }
  
  if(Reset){
      digitalWrite(LATCH_PIN, LOW);
      shiftOut(DS_PIN, CLOCK_PIN, MSBFIRST, 0);
      digitalWrite(LATCH_PIN, HIGH);
      noTone(BUZZ_PIN);
      count = 0;
  }
  

}

