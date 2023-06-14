/*      Author: lab
 *  Partner(s) Name: 
 *      Lab Section:
 *      Assignment: Lab #  Exercise #
 *      Exercise Description: [optional - include for your own benefit]
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 * 
 *      Demo Link:https://youtu.be/FyAJhgkZICk
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
enum STATES{START, SEQUENCE, CORRECT, INCORRECT, GAMEOVER}state;

unsigned char j = 0;
unsigned char i = 0;
unsigned char counter = 0;
unsigned char game[3] = {1, 0, 2};
unsigned char c1[8] = {0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};
unsigned char c2[8] = {0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00};
unsigned char o1[8] = {0xFF, 0x31, 0x42, 0x11, 0x80, 0x04, 0x40, 0x81};
unsigned char o2[8] = {0xFF, 0x42, 0x80, 0x40, 0x31, 0x81, 0x11, 0x40};
unsigned char o3[8] = {0xFF, 0x40, 0x31, 0x42, 0x81, 0x04, 0x80, 0x11};

void Tick_DisplayLED(){
    unsigned char last = (sizeof(game)/sizeof(game[0])) - 1;
    unsigned char input = ~PINB;
    switch(state){
        case START:
            if(input == 0x01){
                state = SEQUENCE;
            }
            else{
                state = START;
            }
            // state = SEQUENCE;
            break;
        case SEQUENCE:
            if(counter < 6){
                counter++;
            }
            else{
                if(j < 3){
                    clearLED();
                    setLED(game[j], 0xFF);
                    j++;
                }
                else{
                    clearLED();
                    state = CORRECT;
                    j = 0;
                }
                counter = 0;
            }
            break;
        case CORRECT:
            if(j < 8){
                if(i < 8){
                    setLED(0, c1[i]);
                    i++;
                }
                else{
                    i = 0;
                }
                j++;
            }
            else if(j < 17){
                if(i < 8){
                    setLED(0, c2[i]);
                    setLED(1, c1[i]);
                    i++;
                }
                else{
                    i = 0;
                }
                j++;
            }
            else if(j < 26){
                if(i < 8){
                    setLED(1, c2[i]);
                    setLED(2, c1[i]);
                    i++;
                }
                else{
                    i = 0;
                }
                j++;
            }
            else{
                j = 0;
                i = 0;
                clearLED();
                state = INCORRECT;
                break;
            }
            break;
        case INCORRECT:
            if(counter < 4){
                counter++;
            }
            else{
                if(j < 8){
                    if(j%2 == 0){
                        setLED(game[last], 0xFF);
                    }
                    else{
                        setLED(game[last], 0x00);
                    }
                    j++;
                }
                else{
                    j = 0;
                    state = GAMEOVER;
                }
                counter = 0;
            }
            break;
        case GAMEOVER:
            if(counter < 6){
                counter++;
            }
            else{
                if(j < 8){
                    PORTA = o1[j];
                    PORTC = o2[j];
                    PORTD = o3[j];
                    j++;
                }
                else{
                    clearLED();
                    j = 0;
                    state = START;
                }
                counter = 0;
            }
            break;
        default:
            break;
    }
    switch(state){
        case START:
            break;
        case SEQUENCE:
            break;
        case CORRECT:
            break;
        case INCORRECT:
            break;
        case GAMEOVER:
            break;
        default:
            break;
    }
}

int main(void) {
    DDRA = 0xFF; PORTA = 0x00;
    DDRB = 0x00; PORTB = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;

    TimerSet(50);
    TimerOn();
    clearLED();

    while (1) {
        Tick_DisplayLED();
        while(!TimerFlag){}
            TimerFlag = 0;
    }
    return 0;
}