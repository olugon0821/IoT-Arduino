const uint8_t PIR {30U};
const uint8_t BUZZ {44U};
enum LED{
  RED = 8,
  GREEN,
  BLUE
};

uint8_t count = 0;

bool PIR_state = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200UL);
  pinMode(BUZZ,OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  bool detect = digitalRead(PIR);
  delay(100UL);
  if(detect){
    if(!PIR_state){
      PIR_state = true;
      Serial.println(F("Comming"));
    }
    digitalWrite(RED,255);
    digitalWrite(GREEN,255);
    digitalWrite(BLUE,255);
    tone(BUZZ, 400);
  }else{
    PIR_state = false;
    digitalWrite(RED,0);
    digitalWrite(GREEN,0);
    digitalWrite(BLUE,0);
    noTone(BUZZ);
  }

}
