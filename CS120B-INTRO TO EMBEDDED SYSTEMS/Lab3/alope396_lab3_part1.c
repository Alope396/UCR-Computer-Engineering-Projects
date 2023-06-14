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
    DDRC = 0xFF; PORTC = 0x00;

    unsigned char count = 0;
    unsigned char tempA = 0x00;
    unsigned char tempB = 0x00;

    while (1) {
        tempA = PINA;
        tempB = PINB;
        for(int i = 0; i < 8; i++){
            if((tempA & 0x01) == 0x01){
                count++;
            }
            tempA = tempA >> 1;
        }
        for(int i = 0; i < 8; i++){
            if((tempB & 0x01) == 0x01){
                count++;
            }
            tempB = tempB >> 1;
        }
        PORTC = count;
        count = 0;
    }
    return 1;
}