#include <avr/io.h> // AVR 칩 메모리 번지수 : ex) PB0 ~
#include <util/delay.h> // delay 헤더 파일
#define F_CPU 16000000UL //CPU 클럭

int main(){
  //pinMode 13 == OUTPUT
  // PORT
  DDRB |= 0x80; // 0b1000000 
  for(;;){
    uint8_t button_state = PINE & 0x20; // 0b0010 0000
    if(button_state){
      PORTB |= 0x80;
    }else{
      PORTB &= ~0x80;
    }
    
  }
  return 0;
}
