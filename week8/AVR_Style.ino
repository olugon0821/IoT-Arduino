#include <avr/io.h> // AVR 칩 메모리 번지수 : ex) PB0 ~
#include <util/delay.h> // delay 헤더 파일
#define F_CPU 16000000UL //CPU 클럭

int main(){
  //pinMode 13 == OUTPUT
  // PORT
  DDRB |= 0x80; // 0b1000000 
  for(;;){
    PORTB |= 0x80;
    _delay_ms(500);
  PORTB &= ~0x80;
    _delay_ms(500);
  }
  return 0;
}
