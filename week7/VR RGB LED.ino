enum RGBLED{
  RED = 8U,
  GREEN, //9
  BLUE // 10
};
const uint8_t VR_PIN {A0};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200UL);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t VR = analogRead(VR_PIN);
  uint16_t value {map(VR,0,1023,0,255)};

  analogWrite(RED,value);
  analogWrite(GREEN,value);
  analogWrite(BLUE,value);
  }
