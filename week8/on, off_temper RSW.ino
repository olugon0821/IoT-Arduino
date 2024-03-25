#include "DHT.h"
const uint8_t TEMP_HUMID {A1};
class DHT dht(TEMP_HUMID,11); // 객체 생성
const uint8_t SW {12U};
bool State = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200UL);
  Serial1.begin(9600UL);
  dht.begin(); // 센서 초기화
  Serial.println("블루투스 레디");
  pinMode(SW,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
    bool dht11_state = dht.read();

  if (Serial.available()) {
    char value = static_cast<char>(Serial.read());
    if (value == '1') {
      Serial.println("작동 시작");
      State = true; // 시스템 활성화
    } else if (value == '0') {
      Serial.println("작동 중지");
      State = false; // 시스템 비활성화
      digitalWrite(SW, LOW); // LED 끄기
    }
  }

  if (State && dht11_state) { // 시스템 활성화 및 센서 읽기 성공 시
    float temperature = dht.readTemperature();
    if (temperature > 25) { // 온도가 25도 이상이면 LED를 켬
      digitalWrite(SW, HIGH);
    }else{
      digitalWrite(SW,LOW);
    }
    Serial.println("작동 중");
    Serial.println(F("온도 : "));
    Serial.println(String(temperature) + String(" C"));
    Serial.println(F("습도 : "));
    Serial.println(String(dht.readHumidity()) + String(" %"));
    Serial.println(F("열 : "));
    Serial.println(String(dht.computeHeatIndex(temperature, dht.readHumidity())) + String(" degree"));
    Serial.println("---------");
  }

  delay(1000UL);
}
