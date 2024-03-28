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
