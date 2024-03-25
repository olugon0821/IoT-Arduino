#include "DHT.h"
const uint8_t TEMP_HUMID {A1};
const uint8_t FS1 {2U}; // pull-up
const uint8_t FS2 {3U}; // pull-down == interrupt
class DHT dht(TEMP_HUMID,11); // 객체 생성
const uint8_t RSW {12U};

volatile uint16_t button_count {0}; // volatile == (최적화 X)변수를 증감시킬때  

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200UL);
  Serial1.begin(9600UL);
  pinMode(FS1,INPUT_PULLUP);
  dht.begin(); // 센서 초기화
  Serial.println("블루투스 레디");
  attachInterrupt(digitalPinToInterrupt(FS2), call911, RISING);
  // FALLING ==> H -> L //RISING ==> L -> H //CHANGE == L -> H or H -> L

}

void call911(){
  ++button_count;
  digitalWrite(RSW,LOW);
  analogWrite(TEMP_HUMID, LOW);
  
  for (int i = 0; i<3; i++){
  Serial.println(F("FIRE!! CALLING 911"));
  Serial.println(F("FIRE!! CALLING 911"));
  }
  Serial.println(button_count);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool dht11_state {dht.read()};

  if(dht11_state){
    float temperature = dht.readTemperature(); // 온도
    float humidity = dht.readHumidity(); // 습도
    float heat = dht.computeHeatIndex(temperature, humidity);
    Serial.print(F("온도 : "));
    Serial.println(String(temperature)+String(" C"));
    delay(500UL);
    Serial.print(F("습도 : "));
    Serial.println(String(humidity)+String(" %"));
    delay(500UL);
    Serial.print(F("열 : "));
    Serial.println(String(heat)+String(" degree"));
    Serial.println("---------");
    delay(500UL);
  }
delay(1000UL);
}
