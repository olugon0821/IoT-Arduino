const uint8_t LED_Pins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const uint8_t LEDNUM = sizeof(LED_Pins) / sizeof(LED_Pins[0]);

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < LEDNUM; ++i) {
    pinMode(LED_Pins[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < LEDNUM; ++i) {
    digitalWrite(LED_Pins[i], HIGH);
    delay(1000UL);
  }

  for (int i = LEDNUM - 1; i >= 0; --i) {
    digitalWrite(LED_Pins[i], LOW);
    delay(1000UL);
  }
}
