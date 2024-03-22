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
    state = true; 
  }
  else if (!SW_value && state) {
    state = false;
  }
  Serial.println(count);

  if(count % 2 == 0){
    analogWrite(RED,100);
    analogWrite(BLUE,100);
  }else{
    analogWrite(RED,0);
    analogWrite(BLUE,0);
  }

}
