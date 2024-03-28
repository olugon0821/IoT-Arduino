#include <IRremote.hpp>
const uint8_t IR {40U};
const uint8_t LED {7U};
class IRrecv irrecv(IR);
class decode_results result; // 디폴트 생성자

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200UL);
  pinMode(LED, OUTPUT);
  irrecv.begin(IR, LED); //13번 핀을 출력용으로 사용

}

void loop() {
  // put your main code here, to run repeatedly:
  if(irrecv.decode()){ // 리모트 동작 감지
  uint8_t data = irrecv.decodedIRData.command;
  Serial.println(data, HEX); // 16진수로 출력  0x16 = 0, 0x0C = 1
  switch(data){
    case 0x16:
      digitalWrite(LED,HIGH);
      break;
    case 0x0C:
      digitalWrite(LED,LOW);
      break;
  }
  irrecv.resume();
  irrecv.start(10);
    }
  }

