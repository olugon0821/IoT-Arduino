#include "HCSR04.h"
#include "DHT.h"

enum ULSN{
  TRIG = 40,
  ECHO
};
const uint8_t TEMP {A1};
const uint8_t BUZZ {11U};
class DHT dht(TEMP,11);

class UltraSonicDistanceSensor ul_sn(TRIG, ECHO);
float tmeperature {TEMP};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200UL);
  pinMode(BUZZ,OUTPUT);
  dht.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  bool dht_value = dht.read();
  
  if(dht_value){
    float temperature = dht.readTemperature();
    float distance = ul_sn.measureDistanceCm(temperature);
    if(distance >= 100 and distance <= 400.0F){
      Serial.println(F("Out of Ranges"));
    }else if(distance >= 50.0F and distance <= 99.9F){
      Serial.println(F("distance : "));
      Serial.println(distance + String(" CM"));
      tone(BUZZ,700);
      delay(500UL);
      noTone(BUZZ);
      delay(100UL);
      

    }else if(distance >=30.0F and distance <= 49.9F){
      Serial.println(F("distance : "));
      Serial.println(distance + String(" CM"));
      tone(BUZZ,600);
      delay(250UL);
      noTone(BUZZ);
      delay(100UL);


    }else if(distance >=20.0F and distance <= 29.9F){
      Serial.println(F("distance : "));
      Serial.println(distance + String(" CM"));
      tone(BUZZ,500);
      delay(125UL);
      noTone(BUZZ);
      delay(100UL);

      
    }else if(distance >= 10.0F and distance <= 19.9F){
      Serial.println(F("distance : "));
      Serial.println(distance + String(" CM"));
      tone(BUZZ,400);
      delay(70UL);
      noTone(BUZZ);
      delay(100UL);


    }else if(distance >= 5.0F and distance <= 9.9F){
      Serial.println(F("distance : "));
      Serial.println(distance + String(" CM"));
      tone(BUZZ,300);
      delay(35UL);
      noTone(BUZZ);
      delay(100UL);

    }else if(distance >= 0.0F and distance <= 4.9F){
      Serial.println(F("distance : "));
      Serial.println(distance + String(" CM"));
      tone(BUZZ,200);
      delay(15UL);
      noTone(BUZZ);
      delay(100UL);

    }
  }
}
