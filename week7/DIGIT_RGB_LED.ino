enum RGB{
  RED = 8U,
  GREEN,
  BLUE
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200UL);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()){
    uint16_t RED_value = Serial.parseInt();
    uint16_t GREEN_value = Serial.parseInt();
    uint16_t BLUE_value = Serial.parseInt();
    if(Serial.read() == '\n'){
      analogWrite(RED,RED_value);
      analogWrite(GREEN,GREEN_value);
      analogWrite(BLUE,BLUE_value);
    }
    delay(10UL);
  }

}
