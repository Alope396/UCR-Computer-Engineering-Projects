/*      Author: lab
 *  Partner(s) Name: 
 *      Lab Section:
 *      Assignment: Lab #  Exercise #
 *      Exercise Description: [optional - include for your own benefit]
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{START, INPUT_1_PRESS, INPUT_1_RELEASE, INPUT_2_PRESS, UNLOCK, LOCK} state;

void Tick(){
    switch(state){//Transitions
        case START:
            state = INPUT_1_PRESS;
            break;
        case INPUT_1_PRESS:
            if(PINA == 0x04){
                state = INPUT_1_RELEASE;
            }
            else{
                state = INPUT_1_PRESS;
            }
            break;
        case INPUT_1_RELEASE:
            if(PINA == 0x00){
                state = INPUT_2_PRESS;
            }
            else{
                state = INPUT_1_RELEASE;
            }
            break;
        case INPUT_2_PRESS:
            if(PINA == 0x02){
                state = UNLOCK;
            }
            else if(PINA == 0x00){
                state = INPUT_2_PRESS;
            }
            else{
                state = INPUT_1_PRESS;
            }
            break;
        case UNLOCK:
            if(PINA == 0x80){
                state = LOCK;
            }
            else{
                state = UNLOCK;
            }
            break;
        case LOCK:
            if(PINA){
                state = LOCK;
            }
            else{
                state = INPUT_1_PRESS;
            }
            break;
        default:
            break;
    }
    switch(state){//Actions
        case START:
            PORTB = 0x00;
            break;
        case INPUT_1_PRESS:
            break;
        case INPUT_1_RELEASE:
            break;
        case INPUT_2_PRESS:
            break;
        case UNLOCK:
            if(PINA == 0x02){
                PORTB = 0x01;
            }
            break;
        case LOCK:
            PORTB = 0x00;
            break;
        default:
            break;
    }
}

int main(void) {
    DDRA = 0x00; PORTA = 0x00;
    DDRB = 0xFF; PORTB = 0x00;
    
    state = START;

    while (1) {
        Tick();
    }
    return 1;
}