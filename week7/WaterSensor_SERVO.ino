const uint8_t WS_PIN {A1};
const uint8_t SERVO {13U};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200UL);
  pinMode(SERVO, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t WS {analogRead(WS_PIN)};
  delay(250);
  
  uint16_t mapped_value {map(WS,0,700,0,255)};
  Serial.println(mapped_value);

  if(0 <= mapped_value && mapped_value <= 130){
    for(int i {0}; i < 255; i+=2){
      analogWrite(SERVO, i);
      delay(10UL);
    }
      for(int i {255}; i >=0 ; i-=2){
      analogWrite(SERVO, i);
      delay(10UL);
    }
      }
    else if(130 <= mapped_value && mapped_value <= 255){
      for(int i {0}; i < 255; i+=10){
        analogWrite(SERVO, i);
        delay(10UL);
      }
      for(int i {255}; i >= 0; i-=10){
        analogWrite(SERVO, i);
        delay(10UL);
      }
    }

}
