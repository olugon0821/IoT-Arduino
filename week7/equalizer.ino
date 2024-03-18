const uint8_t LED_Pins[] {2U, 3U, 4U, 5U, 6U, 7U, 8U, 9U};
const uint8_t VR_PIN {A0}; //54U


void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 8; ++i) {
    pinMode(LED_Pins[i], OUTPUT);
  pinMode(VR_PIN,INPUT); //생략가능
  Serial.begin(115200UL); //시리얼 통신을 통해서 화면에 출력
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t vr_value {analogRead(VR_PIN)};
  uint16_t mapped_value {map(vr_value,0,1023,0,7)};
  Serial.println(mapped_value);
  delay(100UL);

  if (mapped_value == 0){
    for(int i = 0; i < 8; ++i)
    digitalWrite(LED_Pins[i],LOW);
  }

   for (int i = 0; i <= mapped_value; ++i) {
    digitalWrite(LED_Pins[i], HIGH);
  }

  for (int i = mapped_value + 1; i < 8; ++i) {
    digitalWrite(LED_Pins[i], LOW);
    }
  }
