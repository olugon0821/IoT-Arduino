const uint8_t LED_Pins[] {2U, 3U, 4U, 5U, 6U, 7U, 8U, 9U};


void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 8; ++i) {
    pinMode(LED_Pins[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 8; ++i) {
    digitalWrite(LED_Pins[i], HIGH);
    delay(500UL);
  }

  for (int i = 7; i >= 0; --i) {
    digitalWrite(LED_Pins[i], LOW);
    delay(500UL);
  }
}
