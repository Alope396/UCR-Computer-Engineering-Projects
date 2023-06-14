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

enum States{START, OFF_PRESS, OFF_RELEASE, ON_PRESS, ON_RELEASE} state;

void Tick(){
    switch(state){//Transitions
        case START:
            state = OFF_RELEASE;
            break;
        case OFF_RELEASE:
            state = PINA ? ON_PRESS : OFF_RELEASE;
            break;
        case ON_PRESS:
            state = PINA ? ON_RELEASE : ON_PRESS;
            break;
        case ON_RELEASE:
            state = PINA ? OFF_PRESS : ON_RELEASE;
            break;
        case OFF_PRESS:
            state = PINA ? OFF_RELEASE : OFF_PRESS;
        default:
            break;
    }
    switch(state){//Actions
        case START:
            PORTB = 0x01;
            break;
        case OFF_RELEASE:
            break;
        case ON_PRESS:
            PORTB = 0x02;
            break;
        case ON_RELEASE:
            break;
        case OFF_PRESS:
            PORTB = 0x01;
            break;
        default:
            break;
    }
}

int main(void) {
    DDRA = 0x00; PORTA = 0x00;
    DDRB = 0xFF; PORTB = 0x00;
    
    PORTB = 0x01;
    state = START;

    while (1) {
        Tick();
    }
    return 1;
}