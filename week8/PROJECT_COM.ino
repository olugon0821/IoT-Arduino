#include <IRremote.hpp>
#include "DHT.h"
#include "HCSR04.h"
#include <Stepper.h>
#include <LiquidCrystal_I2C.h>
#include <MFRC522Debug.h> 
#include <MFRC522DriverPinSimple.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522v2.h>

// 핀 연결
enum PINS{
  TRIG = 24U,
  ECHO,
  RGB_RED = 8U,
  RGB_GREEN = 9U,
  RGB_BLUE = 10U
};

const uint8_t DHT11_PIN {A1};
const uint8_t BUZZ {7U};
const uint8_t PIR_SENSOR {30U};
const uint8_t IR {40U};
const uint16_t STEP_REVOLUTION {2048U}; // 32 * 64 = 360
const uint8_t SERVO {12U};

// 센서 및 드라이버 객체 생성
class Stepper stepping(STEP_REVOLUTION,42,43,44,45);
class UltraSonicDistanceSensor ul_sn(TRIG, ECHO);
class DHT dht(DHT11_PIN,11);
class LiquidCrystal_I2C lcd(0x3F,16,2);
class MFRC522DriverPinSimple sda_pin(53);
class MFRC522DriverSPI driver {sda_pin};
class MFRC522 mfrc522{driver};
const String MASTER_CARD {String("C2A72B1B")};
class IRrecv irrecv(IR);
class decode_results result; // 디폴트 생성자

bool PIR_state = false;
bool function_state = false;
bool UID_Checking = false;


void setup() {
  // put your setup code here, to run once:
  dht.begin(); // 센서 초기화
  stepping.setSpeed(14); // rpm 14
  lcd.init();
  lcd.home();
  lcd.backlight();
  mfrc522.PCD_Init();
  Serial.begin(115200UL);
  pinMode(RGB_RED, OUTPUT);
  pinMode(RGB_GREEN, OUTPUT);
  pinMode(RGB_BLUE, OUTPUT);
  irrecv.begin(IR, SERVO); // SERVO를 출력용으로 사용  lcd.setCursor(1,0);

  lcd.setCursor(1,0);
  lcd.print("HELLO, WELCOME");
  lcd.setCursor(4,1);
  lcd.print("Entrance");
}

void loop() {
  // put your main code here, to run repeatedly:
    bool dht11_state {dht.read()}; // DHT11 data read
    float temperature = dht.readTemperature(); // 온도
    float humidity = dht.readHumidity(); // 습도
    float heat = dht.computeHeatIndex(temperature, humidity); // 열
    float distance = ul_sn.measureDistanceCm(temperature); // 거리 측정

    LCD_FUNC();

    if(!mfrc522.PICC_IsNewCardPresent()) return;
    if(!mfrc522.PICC_ReadCardSerial()) return;
    String tagID = ""; // 빈문자열
    for(uint8_t i {0U}; i <4; ++i){
      tagID += String(mfrc522.uid.uidByte[i],HEX);
    }
    tagID.toUpperCase(); // 소문자를 대문자로 변환
    mfrc522.PICC_HaltA(); // UID 이외에는 멈춤
    Serial.println(tagID);
    if(tagID == MASTER_CARD){
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("Thank YOU");
      lcd.setCursor(4,1);
      lcd.print("ALLOWED");
      delay(2000UL);
      UID_Checking = true;
      Servo_Move(UID_Checking);
    }else{
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("WARNING");
      lcd.setCursor(2,1);
      lcd.print("Differance ID");
    }
}
// LCD 작동 //
void LCD_FUNC(){
  bool PIR_value {digitalRead(PIR_SENSOR)};
  if(PIR_value){
    if(!PIR_state){
      PIR_state = true;
      Serial.println("OPEN");
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("Entrance");
      lcd.setCursor(6,1);
      lcd.print("OPEN");
      stepping.step(STEP_REVOLUTION / 4);
      delay(1000UL);
    }else{
      Serial.println("CLOSE");
      PIR_state = false;
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("Entrance");
      lcd.setCursor(6,1);
      lcd.print("CLOSE");
      stepping.step(-(STEP_REVOLUTION / 4));
      lcd.clear();
      Distance();
    }
}
}

// // 온도에 따른 LED 작동
void RGB_LED(){

  bool dht11_state {dht.read()}; // DHT11 data read
  float temperature = dht.readTemperature(); // 온도
  if(temperature > 29 ){
    digitalWrite(RGB_BLUE,LOW);
    digitalWrite(RGB_GREEN,LOW);
    digitalWrite(RGB_RED,80);
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print(temperature);
    lcd.setCursor(6,1);
    lcd.print("WARNING!");

  }else if(temperature >=26 and temperature <=29 ){
    digitalWrite(RGB_GREEN,80);
    digitalWrite(RGB_RED,LOW);
    digitalWrite(RGB_BLUE,LOW);
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print(temperature);
    lcd.setCursor(6,1);
    lcd.print("GOOD");

  }else if(temperature >= 20 and temperature <= 25){
    digitalWrite(RGB_BLUE,80);
    digitalWrite(RGB_GREEN,LOW);
    digitalWrite(RGB_RED,LOW);
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print(temperature);
    lcd.setCursor(6,1);
    lcd.print("GOOD");
    UID_CHECK();
    }
}
  
// // 서보모터 작동
void Servo_Move(bool UID_Checking) {
    if (UID_Checking == true) {
        lcd.clear();
        lcd.setCursor(6, 0);
        lcd.print("GATE");
        lcd.setCursor(6, 1);
        lcd.print("OPEN");
        for (int angle = 0; angle <= 180; angle += 5) {
            analogWrite(SERVO, map(angle, 0, 180, 0, 255));
            delay(15); 
        }
        delay(1000UL);
        lcd.clear();
        lcd.setCursor(6, 0);
        lcd.print("GATE");
        lcd.setCursor(6, 1);
        lcd.print("CLOSE");
        for (int angle = 180; angle >= 0; angle -= 5) {
            analogWrite(SERVO, map(angle, 0, 180, 0, 255));
            delay(15); // 서보 모터가 움직이는 속도 조절을 위한 딜레이
        }
    }
}


void Distance(){
  bool dht_value = dht.read();
  while(function_state == false){
    if(dht_value){
    float temperature = dht.readTemperature();
    float distance = ul_sn.measureDistanceCm(temperature);
    Serial.println(distance);
    if(distance > 0 and distance <= 20){
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("Thank You");
        lcd.setCursor(3,1);
        lcd.print("Recognizing");
        delay(2000UL);
        RGB_LED();
        break;

    }else if(distance > 20){
        lcd.clear();
        lcd.setCursor(6,0);
        lcd.print(distance);
        lcd.setCursor(3,1);
        lcd.print("Come Closer");
      }
      delay(10UL);
      }
    }
    RGB_LED();
}


void UID_CHECK(){
  bool UID_state = false;
  delay(1000UL);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Please, Tag");
  lcd.setCursor(2,1);
  lcd.print("Your ID Card");
}
