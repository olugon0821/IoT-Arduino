#include "DHT.h"

enum CONTROL_PINS{
  TEMPER_HUMID = A0,
  RED_LED = 8U,
  BLUE_LED
};

class DHT dht(TEMPER_HUMID, 11); // dht 객체 생성

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200UL);
  dht.begin(); // dht 초기화
  pinMode(TEMPER_HUMID, INPUT);
  pinMode(RED_LED,OUTPUT);
  pinMode(BLUE_LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(dht.read()){
    
    const float temperature {dht.readTemperature()};
    const float humidity {dht.readHumidity()};
    const String sending_data {String(temperature)+ "," + String(humidity)}; // ex) [23.30,50.00]
    
    Serial.println(sending_data);

    if(Serial.available()){
      const String in_comming_data {Serial.readStringUntil('\n')}; // 입력한 문자열을 \n 까지 받음
      if(in_comming_data.equals("RED_LED_ON")){
        digitalWrite(RED_LED, HIGH);
      }else if(in_comming_data.equals("RED_LED_OFF")){
        digitalWrite(RED_LED, LOW);
      }else if(in_comming_data.equals("BLUE_LED_ON")){
        digitalWrite(BLUE_LED, HIGH);
      }else if(in_comming_data.equals("BLUE_LED_OFF")){
        digitalWrite(BLUE_LED, LOW);
      }else{}
    }
    delay(500UL);
  }
}
