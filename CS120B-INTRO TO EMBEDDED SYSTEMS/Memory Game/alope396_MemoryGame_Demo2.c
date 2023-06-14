/*      Author: lab
 *  Partner(s) Name: 
 *      Lab Section:
 *      Assignment: Lab #  Exercise #
 *      Exercise Description: [optional - include for your own benefit]
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 *      
 *      First Complexity: LED Matrix
 *      Second Complexity: Joystick
 * 
 *      Demo Link:https://youtu.be/ySsDQFSbBVE
 */
#include <avr/io.h>
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

void ADC_init(){
    ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<< ADATE);
}

void clearLED(){
    PORTA = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
}

void setLED(unsigned char x, unsigned char y){
    if(x == 0){
        PORTD = y;
    }
    else if(x == 1){
        PORTA = y;
    }
    else if(x == 2){
        PORTC = y;
    }
    else{
        return;
    }
}

enum STATE{START, SELECT}state;

unsigned char pos = 1;
void Tick_TestJoystick(){
    unsigned short x = ADC;
    unsigned char button = (~PINB & 0x01);
    unsigned char input = (~PINB & 0x02);
    switch(state){
        case START:
            if(button == 0x01){
                state = SELECT;
            }
            break;
        case SELECT:
            if(x < 400 && pos > 0){
                pos--;
            }
            else if(x > 600 && pos < 2){
                pos++;
            }
            state = SELECT;
            break;
        default:
            break;
    }
    switch(state){
        case START:
            break;
        case SELECT:
            clearLED();
            setLED(pos, 0xFF);
            break;
        default:
            break;
    }
}

int main(void) {
    DDRA = 0xFE; PORTA = 0x00;
    DDRB = 0x00; PORTB = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;

    TimerSet(200);
    TimerOn();
    clearLED();
    ADC_init();

    while (1) {
        Tick_TestJoystick();
        while(!TimerFlag){}
            TimerFlag = 0;
    }
    return 0;
}