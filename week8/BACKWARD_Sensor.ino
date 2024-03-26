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
    }else if(distance >= 50.0F and distance <= 99.0F){
      Serial.println(F("distance : "));
      Serial.println(distance + String(" CM"));
      tone(BUZZ,200);
      delay(500UL);
      noTone(BUZZ);
      

    }else if(distance >=30.0F and distance <= 49.0F){
      Serial.println(F("distance : "));
      Serial.println(distance + String(" CM"));
      tone(BUZZ,200);
      delay(125UL);
      noTone(BUZZ);
      delay(125UL);

    }else if(distance >=20.0F and distance <= 29.0F){
      Serial.println(F("distance : "));
      Serial.println(distance + String(" CM"));
      tone(BUZZ,200);
      delay(70UL);
      noTone(BUZZ);
      
    }else if(10.0F <= distance and distance <= 19.0F){
      Serial.println(F("distance : "));
      Serial.println(distance + String(" CM"));
      tone(BUZZ,200);
      delay(40UL);
      noTone(BUZZ);
      

    }else if(5.0F <= distance and distance <= 9.0F){
      Serial.println(F("distance : "));
      Serial.println(distance + String(" CM"));
      tone(BUZZ,200);
      delay(10UL);
      noTone(BUZZ);
      

    }else if(2.0F <= distance and distance <= 4.0F){
      Serial.println(F("distance : "));
      Serial.println(distance + String(" CM"));
      tone(BUZZ,200);
      delay(1UL);
      noTone(BUZZ);
      

    }
  
  delay(500UL);
  }
 
}
