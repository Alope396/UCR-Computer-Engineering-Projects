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
    DDRD = 0x00; PORTD = 0x00;
    DDRB = 0xFE; PORTB = 0x00;

    unsigned int totalWeight = 0;
    unsigned char tempB = PORTB;
    while (1) {
        totalWeight = (PIND << 1)+ (PINB & 0x01);
        if(totalWeight >= 70){
            PORTB = (tempB | 0x02);
        }
        else if((totalWeight > 5) && (totalWeight <= 70)){
            PORTB = (tempB | 0x04);
        }
        else{
            PORTB = (tempB & 0x01);
        }
    }
    return 1;
}