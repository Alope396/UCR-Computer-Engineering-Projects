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

// enum States{START, ONE_PRESS, ONE_RELEASE, BOTH_PRESS, BOTH_RELEASE} state;
enum States{START, WAIT, I_PRESS, I_RELEASE, D_PRESS, D_RELEASE, Z_PRESS, Z_RELEASE} state;

void Tick(){
    switch(state){
        case START:
            state = WAIT;
            break;
        case WAIT:
            if(PINA == 0x01){
                state = I_PRESS;
            }
            else if(PINA == 0x02){
                state = D_PRESS;
            }
            else if(PINA == 0x03){
                state = Z_PRESS;
            }
            else{
                state = WAIT;
            }
            break;
        case I_PRESS:
            if(PINA == 0x03){
                state = Z_PRESS;
            }
            else{
                state = I_RELEASE;
            }
            break;
        case I_RELEASE:
            if(PINA == 0x01){
                state = I_RELEASE;
            }
            else if(PINA == 0x03){
                state = Z_PRESS;
            }
            else{
                state = WAIT;
            }
            break;
        case D_PRESS:
            if(PINA == 0x03){
                state = Z_PRESS;
            }
            else{
                state = D_RELEASE;
            }
            break;
        case D_RELEASE:
            if(PINA == 0x02){
                state = D_RELEASE;
            }
            else if(PINA == 0x03){
                state = Z_PRESS;
            }
            else{
                state = WAIT;
            }
            break;
        case Z_PRESS:
            state = Z_RELEASE;
            break;
        case Z_RELEASE:
            if(PINA == 0x03){
                state = Z_RELEASE;
            }
            else if(PINA == 0x02){
                state = D_PRESS;
            }
            else if(PINA == 0x01){
                state = I_PRESS;
            }
            else{
                state = WAIT;
            }
            break;
        default:
            break;
    }
    switch (state){
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
    // unsigned char tempPA0 = (PINA & 0x01) == 0x01;
    // unsigned char tempPA1 = (PINA & 0x02) == 0x02;
    // unsigned char last = 0x00;
    // switch(state){//Transitions
    //     case START:
    //         if((PINA == 0x01) || (PINA == 0x02) || (PINA == 0x03)){
    //             if(PINA == 0x03){
    //                 state = BOTH_PRESS;
    //             }
    //             else{
    //                 state = ONE_PRESS;
    //             }
    //         }
    //         break;
    //     case ONE_PRESS:
    //         if(PINA == 0x03){
    //             state = BOTH_PRESS;
    //         }
    //         else{
    //             last = PINA;
    //             state = ONE_RELEASE;
    //         }
    //         break;
    //     case ONE_RELEASE:
    //         if(PINA == 0x00){
    //             state = START;
    //         }
    //         else{
    //             if(PINA == 0x03){
    //                 state = BOTH_PRESS;
    //             }
    //             else if(PINA != last){
    //                 state = ONE_PRESS;
    //             }
    //             else{
    //                 state = ONE_RELEASE;
    //             }
    //         }
    //         break;
    //     case BOTH_PRESS:
    //         if((PINA == 0x01) || (PINA == 0x02)){
    //             state = ONE_PRESS;
    //         }
    //         else{
    //             state = BOTH_RELEASE;
    //         }
    //         break;
    //     case BOTH_RELEASE:
    //         if(PINA == 0x00){
    //             state = START;
    //         }
    //         else{
    //             if(PINA == 0x03){
    //                 state = BOTH_PRESS;
    //             }
    //             else{
    //                 state = ONE_PRESS;
    //             }
    //         }
    //         break;
    //     default:
    //         break;
    // }
    // switch(state){//Actions
    //     case START:
    //         break;
    //     case ONE_PRESS:
    //         if((PINA == 0x01) && (PORTC < 9)){
    //             PORTC = PORTC + 1;
    //         }
    //         else if(PORTC > 0){
    //             PORTC = PORTC - 1;
    //         }
    //         break;
    //     case ONE_RELEASE:
    //         break;
    //     case BOTH_PRESS:
    //         PORTC = 0;
    //         break;
    //     case BOTH_RELEASE:
    //         break;
    //     default:
    //         break;
    // }
}

int main(void) {
    DDRA = 0x00; PORTA = 0x00;
    DDRB = 0xFF; PORTB = 0x00;

    PORTC = 7;
    state = START;

    while (1) {
        Tick();
    }
    return 1;
}