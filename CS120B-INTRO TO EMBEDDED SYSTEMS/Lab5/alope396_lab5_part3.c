/*      Author: lab
 *  Partner(s) Name: 
 *      Lab Section:
 *      Assignment: Lab #  Exercise #
 *      Demo link: https://youtu.be/loXmmJ4VAo8
 *      Exercise Description: [optional - include for your own benefit]
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{START, WAIT, FIRST_PRESS, FIRST_RELEASE, NEXT_PRESS, NEXT_RELEASE, OFF_PRESS, OFF_RELEASE} state;

void Tick(){
    unsigned char input = 0x00;
    input = (~PINA & 0x01);

    switch(state){
        case START:
            break;
        case FIRST_PRESS:
            if(input == 0x01){
                state = FIRST_RELEASE;
                break;
            }
            else{
                state = FIRST_PRESS;
                break;
            }
        case FIRST_RELEASE:
            if(input == 0x00){
                state = NEXT_PRESS;
            }
            else{
                state = FIRST_RELEASE;
            }
            break;
        case NEXT_PRESS:
            if(input == 0x01){
                state = NEXT_RELEASE;
                break;
            }
            else{
                state = NEXT_PRESS;
                break;
            }
        case NEXT_RELEASE:
            if(input == 0x00){
                state = OFF_PRESS;
            }
            else{
                state = NEXT_RELEASE;
            }
            break;
        case OFF_PRESS:
            if(input == 0x01){
                state = OFF_RELEASE;
                break;
            }
            else{
                state = OFF_PRESS;
                break;
            }
        case OFF_RELEASE:
            if(input == 0x00){
                state = FIRST_PRESS;
            }
            else{
                state = OFF_RELEASE;
            }
            break;
        default:
            break;
    }
    switch(state){
        case START:
            state = FIRST_PRESS;
            PORTC = 0x00;
            break;
        case FIRST_PRESS:
            PORTC = 0xAA;
            break;
        case FIRST_RELEASE:
            break;
        case NEXT_PRESS:
            PORTC = 0x55;
            break;
        case NEXT_RELEASE:
            break;
        case OFF_PRESS:
            PORTC = 0x00;
            break;
        case OFF_RELEASE:
            break;
        default:
            break;
    }
}

int main(void) {
    DDRA = 0x00; PORTA = 0x11;
    DDRC = 0xFF; PORTC = 0x00;

    state = START;

    while (1) {
        Tick();
    }
    return 1;
}