#include <avr/io.h>
#include <avr/eeprom.h>
#ifdef _SIMULATE_
#include <avr/interrupt.h>
#include "simAVRHeader.h"
#endif

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

volatile unsigned char TimerFlag = 0;
void TimerISR(){TimerFlag = 1;}
void TimerSet(unsigned long M){
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}
void TimerOn(){
    TCCR1B = 0x0B;
    OCR1A = 125;
    TIMSK1 = 0x02;
    TCNT1 = 0;
    _avr_timer_cntcurr = _avr_timer_M;
    SREG |= 0x80;
}
void TimerOff(){
    TCCR1B = 0x00;
}
ISR(TIMER1_COMPA_vect){
    _avr_timer_cntcurr--;
    if(_avr_timer_cntcurr == 0){
        TimerISR();
        _avr_timer_cntcurr = _avr_timer_M;
    }
}
//C3 CLEAR
//C2 CLOCK
//C1 LATCH
//C0 Data Line

void transmit_data(unsigned char data) {
    int i;
    for (i = 0; i < 8 ; ++i) {
        PORTC = 0x08;
        PORTC |= ((data >> i) & 0x01);
        PORTC |= 0x02;  
    }
    PORTC |= 0x04;
    PORTC = 0x00;
}


int main(void) {
    DDRC = 0xFF; PORTC = 0x00;
    
    TimerSet(500);
    TimerOn();

    while(1){
        transmit_data(0xFF);
        while(!TimerFlag){}
        TimerFlag = 0;
    }
    return 0;
}