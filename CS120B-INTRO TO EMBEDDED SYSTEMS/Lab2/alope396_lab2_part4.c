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

int main(void) {
    DDRA = 0x00; PORTA = 0x00;
    DDRB = 0x00; PORTB = 0x00;
    DDRC = 0x00; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;

    unsigned char totalWeight = 0x00;

    while (1) {
        totalWeight = PINA + PINB + PINC;
        if(PINA > PINC){
            if(PINA - PINC > 0x50){
                PORTD = 0x02;
            }
        }
        else{
            if(PINC - PINA > 0x50){
                PORTD = 0x02;
            }
        }
        if(totalWeight > 0x8C){
            PORTD = PORTD | 0x01;
        }
        totalWeight = totalWeight >> 2;
        PORTD = (PORTD | totalWeight);
        if(PORTD == 0x23){
            PORTD = 0x22;
        }
    }
    return 1;
}