// DHT11 //

#include "DHT.h"
class DHT dht(TEMP_HUMID,11); // 객체 생성

setup()
dht.begin(); // 센서 초기화

loop()
bool dht11_state {dht.read()};
analogWrite(TEMP_HUMID, LOW);
float temperature = dht.readTemperature(); // 온도
float humidity = dht.readHumidity(); // 습도
float heat = dht.computeHeatIndex(temperature, humidity);



// Ultra Sonic Sensor //

#include "HCSR04.h"
enum ULSN{
  TRIG = 40,
  ECHO
};
class UltraSonicDistanceSensor ul_sn(TRIG, ECHO);

loop()
float distance = ul_sn.measureDistanceCm(temperature);



// Step Motor //

#include <Stepper.h>
const uint16_t STEP_REVOLUTION {2048U}; // 32 * 64 = 360
class Stepper stepping(STEP_REVOLUTION,42,43,44,45);

setup()
stepping.setSpeed(14); // rpm 14

loop()
stepping.step(STEP_REVOLUTION);



// LCD //

#include <LiquidCrystal_I2C.h>
class LiquidCrystal_I2C lcd(0x3F,16,2);

setup()
lcd.init();
lcd.home();
lcd.backlight();

loop()
lcd.setCursor(0,0);
lcd.print();
lcd.clear();



// RFID //

#include <MFRC522Debug.h> 
#include <MFRC522DriverPinSimple.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522v2.h>

class MFRC522DriverPinSimple sda_pin(53); //driver 객체 생성
class MFRC522DriverSPI driver {sda_pin};
class MFRC522 mfrc522{driver};

const String MASTER_CARD {String("C2A72B1B")};

setup()
mfrc522.PCD_Init();

loop()
if(!mfrc522.PICC_IsNewCardPresent()) return;
if(!mfrc522.PICC_ReadCardSerial()) return;
String tagID = ""; // 빈문자열
for(uint8_t i {0U}; i <4; ++i){
  tagID += String(mfrc522.uid.uidByte[i],HEX);
}
tagID.toUpperCase(); // 소문자를 대문자로 변환
mfrc522.PICC_HaltA(); // UID 이외에는 멈춤
