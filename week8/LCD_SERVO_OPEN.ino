#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include "HCSR04.h"

enum PINS{
  HUMID = A1,
  TRIG = 30,
  ECHO,
  SERVO = 13
};

class DHT dht(HUMID,11);
class UltraSonicDistanceSensor ul_sn(TRIG, ECHO);
class LiquidCrystal_I2C lcd(0x3F,16,2);
bool open = false;

void setup() {
  Serial.begin(115200UL);
  dht.begin();
  lcd.init();
  lcd.home();
  lcd.backlight();
  pinMode(SERVO, OUTPUT);
}

void moveServo(bool open) {
  if (open) {
    for (int i = 0; i < 255; i += 10){
      analogWrite(SERVO, i);
      delay(10UL);
    }
  } else {
    for (int i = 255; i >= 0; i -= 10){
      analogWrite(SERVO, i);
      delay(10UL);
    }
  }
}

void loop() {
  if(dht.read()) {
    float temperature = dht.readTemperature();
    float distance = ul_sn.measureDistanceCm(temperature);
    lcd.setCursor(0,0);
    lcd.print(distance);
    delay(500UL);
    
    if(distance > 20.0F && !open) {
      lcd.setCursor(0,1);
      lcd.print("Welcome");
      delay(10UL);
      moveServo(true);
      open = true;

    } else if(distance >= 0 && distance <= 20.0F && open) {
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("PASS");
      delay(10UL);
      moveServo(false);
      open = false;
    }
  }
}
