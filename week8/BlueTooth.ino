const uint8_t RSW {12U};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200UL);
  Serial1.begin(9600UL); // bluetooth 연결
  pinMode(RSW, OUTPUT);
}

void loop() {
  // peut your main code here, to run repeatedly:
  if(Serial1.available()){. // bluetooth 값이 들어오면
    char input_value = static_cast<char>(Serial1.read());
    if(input_value == '1'){
      digitalWrite(RSW, HIGH);
      Serial1.println(F("Switch on"));
    }else if(input_value == '0'){
      digitalWrite(RSW, LOW);
      Serial1.println(F("Switch off"));
    }
  }
}
