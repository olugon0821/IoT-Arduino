enum LED{
  RED = 8U,
  GREEN,
  BLUE
};
const uint8_t SW1 {40U};

static int count {0};

bool state = false;

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  Serial.begin(115200UL);

}

void loop() {
  // put your main code here, to run repeatedly:
  bool SW_value {digitalRead(SW1)};

  if (SW_value && !state){
    count++;
    Serial.println(count);
    state = true;
    if(count >= 5) count = 1; // 3 이상일 경우 0으로 초기화하여 무한 순환
    
    switch(count) {
      case 1:
        digitalWrite(RED, HIGH);
        digitalWrite(GREEN, LOW);
        digitalWrite(BLUE, LOW);
        break;
      case 2:
        digitalWrite(RED, LOW);
        digitalWrite(GREEN, HIGH);
        digitalWrite(BLUE, LOW);
        break;
      case 3:
        digitalWrite(RED, LOW);
        digitalWrite(GREEN, LOW);
        digitalWrite(BLUE, HIGH);
        break;
      case 4:
        digitalWrite(RED, LOW);
        digitalWrite(GREEN, LOW);
        digitalWrite(BLUE, LOW);
    }
  }
  else if (!SW_value && state) {
    state = false;
  }
}
