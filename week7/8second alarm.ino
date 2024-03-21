const uint8_t pins[] {22,23,24,25,26,27,28,29};
const uint8_t numbers[] {
  0b11111100, // 0
  0b01100000, // 1
  0b11011010, // 2
  0b11110010, // 3
  0b01100110, // 4
  0b10110110, // 5
  0b10111110, // 6
  0b11100100, // 7
  0b11111110, // 8
  0b11100110  // 9
};

const uint8_t BUZZ_PIN {44U};
const uint8_t SWITCH_PIN {42U};
const uint8_t SWITCH_PIN2 {40U};

bool s1 = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(BUZZ_PIN, OUTPUT);
  Serial.begin(115200UL);

  for (auto pin : pins){
    pinMode(pin, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  bool start = digitalRead(SWITCH_PIN);
  bool stop = digitalRead(SWITCH_PIN2);
  
  if (start && !s1) {
    isRunning = true;
  }
  
  if (s1) {
    Start();
  }

  if (stop) {
    isRunning = false;
    Stop();
  }
    
}


void Start(){
  for(auto number : numbers){
    if(digitalRead(SWITCH_PIN2)){
      Stop();
      return;
    }
    for(uint8_t digit{0U}; digit < 8; ++digit){
      if(bitRead(number,digit)){
        digitalWrite(pins[digit], HIGH);
      }else{
        digitalWrite(pins[digit], LOW);
      }
    }
    delay(1000);
    if(number == numbers[9]){
      tone(BUZZ_PIN,300);
    }else{
      noTone(BUZZ_PIN);
    }
  }
}

void Stop(){
  for(uint8_t digit{0U}; digit < 8; ++digit){
      if(bitRead(numbers[0],digit)){
        digitalWrite(pins[digit], HIGH);
      }else{
        digitalWrite(pins[digit], LOW);
      }
  }
}
