#include <IRremote.h>
#include "DHT.h"
#include "HCSR04.h"
#include <Stepper.h>
#include <LiquidCrystal_I2C.h>
#include <MFRC522Debug.h> 
#include <MFRC522DriverPinSimple.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522v2.h>

// 메뉴 상태
enum MenuState {
  MENU_MAIN,
  MENU_PIR,
  MENU_RGB_LED,
  MENU_SERVO
};

// 현재 메뉴 상태
MenuState currentMenu = MENU_MAIN;

// 핀 연결
enum PINS {
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
Stepper stepping(STEP_REVOLUTION,42,43,44,45);
UltraSonicDistanceSensor ul_sn(TRIG, ECHO);
DHT dht(DHT11_PIN,11);
LiquidCrystal_I2C lcd(0x3F,16,2);
MFRC522DriverPinSimple sda_pin(53);
MFRC522DriverSPI driver {sda_pin};
MFRC522 mfrc522{driver};
const String MASTER_CARD {String("C2A72B1B")};
IRrecv irrecv(IR);
decode_results result; // 디폴트 생성자

bool PIR_state = false;

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
  irrecv.enableIRIn(); // IR 리시버 활성화
}

void loop() {
  // put your main code here, to run repeatedly:
  bool dht11_state {dht.read()}; // DHT11 data read
  float temperature = dht.readTemperature(); // 온도
  float humidity = dht.readHumidity(); // 습도
  float heat = dht.computeHeatIndex(temperature, humidity); // 열
  float distance = ul_sn.measureDistanceCm(temperature); // 거리 측정

  switch (currentMenu) {
    case MENU_MAIN:
      handleMainSelection();
      break;
    case MENU_PIR:
      LCD_FUNC();
      break;
    case MENU_RGB_LED:
      RGB_LED();
      break;
    case MENU_SERVO:
      Servo_Move();
      break;
    default:
      break;
  }
}


void handleMainSelection() {
  if (irrecv.decode()) {
    uint8_t data = irrecv.decodedIRData.command;
    switch (data) {
      case 0x45:
        currentMenu = MENU_PIR; // PIR 메뉴로 전환
        break;
      case 0x46:
        currentMenu = MENU_RGB_LED; // RGB LED 메뉴로 전환
        break;
      case 0x47:
        currentMenu = MENU_SERVO; // Servo 메뉴로 전환
        break;
      default:
        break;
    }
    irrecv.resume();
  }
}

void LCD_FUNC() {
  bool PIR_value {digitalRead(PIR_SENSOR)};
  lcd.setCursor(1,0);
  lcd.print("HELLO, WELCOME");
  lcd.setCursor(4,1);
  lcd.print("Entrance");
  if (PIR_value) {
    if (!PIR_state) {
      PIR_state = true;
      Serial.println("OPEN");
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("Entrance");
      lcd.setCursor(6,1);
      lcd.print("OPEN");
      stepping.step(STEP_REVOLUTION / 4);
      delay(500UL);
    } else {
      Serial.println("CLOSE");
      PIR_state = false;
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("Entrance");
      lcd.setCursor(6,1);
      lcd.print("CLOSE");
      stepping.step(-(STEP_REVOLUTION / 4));
    }
    lcd.clear();
  }
  if (irrecv.decode()) {
    irrecv.resume();
  }
}

void RGB_LED() {
  bool dht11_state {dht.read()}; // DHT11 data read
  float temperature = dht.readTemperature(); // 온도
  if (temperature > 29 ) {
    digitalWrite(RGB_BLUE,LOW);
    digitalWrite(RGB_GREEN,LOW);
    digitalWrite(RGB_RED,80);
  } else if (temperature >= 26 and temperature <= 29 ) {
    digitalWrite(RGB_GREEN,80);
    digitalWrite(RGB_RED,LOW);
    digitalWrite(RGB_BLUE,LOW);
  } else if (temperature >= 20 and temperature <= 25) {
    digitalWrite(RGB_BLUE,80);
    digitalWrite(RGB_GREEN,LOW);
    digitalWrite(RGB_RED,LOW);
  }
}

void Servo_Move() {
  if (irrecv.decode()) { // 리모트 동작 감지
    uint8_t data = irrecv.decodedIRData.command;
    switch (data) {
      case 0x16:
        for (int i {0}; i < 256; ++i) {
          analogWrite(SERVO,i);
        }
        break;
      case 0x0C:
        analogWrite(SERVO,50);
        break;
    }
    irrecv.resume();
  }
}
