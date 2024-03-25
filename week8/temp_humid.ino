#include "DHT.h"
const uint8_t TEMP_HUMID {A1};
class DHT dht(TEMP_HUMID,11); // 객체 생성

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200UL);
  Serial1.begin(9600UL);
  dht.begin(); // 센서 초기화
  Serial.println("블루투스 레디");

}

void loop() {
  // put your main code here, to run repeatedly:
  bool dht11_state {dht.read()};

  if(dht11_state){
    float temperature = dht.readTemperature(); // 온도
    float humidity = dht.readHumidity(); // 습도
    Serial.println(F("온도 : "));
    Serial.println(String(temperature)+String(" C"));
    Serial.println(F("습도 : "));
    Serial.println(String(humidity)+String(" %"));
    float heat = dht.computeHeatIndex(temperature, humidity);
    Serial.println(F("열 : "));
    Serial.println(String(heat)+String(" degree"));
    Serial.println("---------");
  }
delay(1000UL);
}
