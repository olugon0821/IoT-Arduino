enum RGBLED{
  RED = 8U,
  GREEN, //9
  BLUE // 10
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
  for(int i {0}; i < 256; ++i){
  analogWrite(RED,i);
  analogWrite(GREEN,i);
  analogWrite(BLUE,i);
  delay(10UL);  // PWM 신호값 출력 0 ~ 255 (2^8)
  }
  delay(100);
  for(int i {255}; i >= 0; --i){
  analogWrite(RED,i);
  analogWrite(GREEN,i);
  analogWrite(BLUE,i);
  delay(10UL);  // PWM 신호값 출력 0 ~ 255 (2^8)
  }
}
