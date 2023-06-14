/*      Author: lab
 *  Partner(s) Name: 
 *      Lab Section:
 *      Assignment: Lab #  Exercise #
 *      Exercise Description: [optional - include for your own benefit]
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 * 
 *      Demo Link: https://youtu.be/FA44tCOXCIk
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include <avr/interrupt.h>
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

enum States{START, FIRST, SEC, LAST, PAUSE} state;

void Tick(){
    unsigned char input = 0;
    input = (~PINA & 0x01);
    switch(state){
        case START:
            state = FIRST;
            break;
        case FIRST:
            if(input == 0x01){
                state = PAUSE;
            }
            else{
                state = SEC;
            }
            break;
        case SEC:
            if(input == 0x01){
                state = PAUSE;
            }
            else{
                state = LAST;
            }
            break;
        case LAST:
            if(input == 0x01){
                state = PAUSE;
            }
            else{
                state = FIRST;
            }
            break;
        case PAUSE:
            if(input == 0x01){
                state = FIRST;
            }
            else{
                state = PAUSE;
            }
            break;
        default:
            break;
    }
    switch(state){
        case START:
            PORTB = 0;
            break;
        case FIRST:
            PORTB = 0x01;
            break;
        case SEC:
            PORTB = 0x02;
            break;
        case LAST:
            PORTB = 0x04;
            break;
        case PAUSE:
            break;
        default:
            break;
    }
}

int main(void) {
    DDRA = 0x00; PORTA = 0x11;
    DDRB = 0xFF; PORTB = 0x00;

    TimerSet(300);
    TimerOn();

    state = START;

    while (1) {
        Tick();
        while(!TimerFlag){}
        TimerFlag = 0;
    }
    return 1;
}