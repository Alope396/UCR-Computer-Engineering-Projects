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
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;

    unsigned char upper = PINA;
    unsigned char lower = PINA;
    unsigned char tempB = PORTB;
    unsigned char tempC = PORTC;

    while (1) {
        upper = PINA & 0xF0;
        lower = PINA & 0x0F;

        PORTB = ((tempB & 0xF0) | (upper >> 4));
        PORTC = ((tempC & 0x0F) | (lower << 4));
    }
    return 1;
}