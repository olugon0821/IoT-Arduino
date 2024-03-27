#include <MFRC522Debug.h> //
#include <MFRC522DriverPinSimple.h> //
#include <MFRC522DriverSPI.h> //
#include <MFRC522v2.h> //
#include <Stepper.h>
// Card UID: C2 A7 2B 1B 
const uint16_t STEP {2048U};
class Stepper stepping{STEP,42,43,44,45};

class MFRC522DriverPinSimple sda_pin(53); //driver 객체 생성
class MFRC522DriverSPI driver {sda_pin};
class MFRC522 mfrc522{driver};

const String MASTER_CARD {String("C2A72B1B")};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200UL);
  mfrc522.PCD_Init();
  stepping.setSpeed(14);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(!mfrc522.PICC_IsNewCardPresent()) return;
  if(!mfrc522.PICC_ReadCardSerial()) return;
  String tagID = ""; // 빈문자열
  for(uint8_t i {0U}; i <4; ++i){
    tagID += String(mfrc522.uid.uidByte[i],HEX);
  }
  tagID.toUpperCase(); // 소문자를 대문자로 변환
  mfrc522.PICC_HaltA(); // UID 이외에는 멈춤
  if(tagID == MASTER_CARD){
    Serial.println(F("카드 일치, 문이 열립니다."));
    stepping.step(STEP);
    delay(500UL);
    stepping.step(-STEP);
  }else{
    Serial.println(F("카드가 다릅니다."));
  }
  

}
