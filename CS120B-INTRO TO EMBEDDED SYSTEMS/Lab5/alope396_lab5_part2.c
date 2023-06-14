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

enum States{START, WAIT, I_PRESS, I_RELEASE, D_PRESS, D_RELEASE, Z_PRESS, Z_RELEASE} state;

void Tick(){
    unsigned char input = 0x00;
    input = ~PINA;

    switch(state){
        case START:
            state = WAIT;
            break;
        case WAIT:
            if(input == 0x01){
                state = I_PRESS;
                break;
            }
            else if(input == 0x02){
                state = D_PRESS;
                break;
            }
            else if(input == 0x03){
                state = Z_PRESS;
                break;
            }
            else{
                state = WAIT;
                break;
            }
        case I_PRESS:
            if(input == 0x03){
                state = Z_PRESS;
                break;
            }
            else{
                state = I_RELEASE;
                break;
            }
        case I_RELEASE:
            if(input == 0x00){
                state = WAIT;
                break;
            }
            else if(input == 0x01){
                state = I_RELEASE;
                break;
            }
            else if(input == 0x03){
                state = Z_PRESS;
                break;
            }
        case D_PRESS:
            if(input == 0x03){
                state = Z_PRESS;
                break;
            }
            else{
                state = D_RELEASE;
                break;
            }
        case D_RELEASE:
            if(input == 0x00){
                state = WAIT;
                break;
            }
            else if(input == 0x02){
                state = D_RELEASE;
                break;
            }
            else if(input == 0x03){
                state = Z_PRESS;
                break;
            }
        case Z_PRESS:
            state = Z_RELEASE;
            break;
        case Z_RELEASE:
            if(input == 0x00){
                state = WAIT;
                break;
            }
            else if(input == 0x01){
                state = I_PRESS;
                break;
            }
            else if(input == 0x02){
                state = D_PRESS;
                break;
            }
            else if(input == 0x03){
                state = Z_RELEASE;
                break;
            }
        default:
            break;
    }
    switch(state){
        case START:
            PORTC = 7;
            break;
        case WAIT:
            break;
        case I_PRESS:
            if(PORTC < 9){
                PORTC = PORTC + 1;
            }
            break;
        case I_RELEASE:
            break;
        case D_PRESS:
            if(PORTC > 0){
                PORTC = PORTC - 1;
            }
            break;
        case D_RELEASE:
            break;
        case Z_PRESS:
            PORTC = 0;
            break;
        case Z_RELEASE:
            break;
        default:
            break;
    }
}

int main(void) {
    DDRA = 0x00; PORTA = 0x11;
    DDRC = 0xFF; PORTC = 0x00;

    state = START;
    PORTC = 7;

    while (1) {
        Tick();
    }
    return 1;
}