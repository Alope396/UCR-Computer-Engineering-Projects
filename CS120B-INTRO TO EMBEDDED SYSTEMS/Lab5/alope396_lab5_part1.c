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
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    unsigned char fuel = 0x00;

    while (1) {
        fuel = (~PINA & 0x0F);
        if(fuel <= 0x04){
            if((fuel == 0x03) || fuel == (0x04)){
                PORTC = 0x70;
            }
            else if((fuel == 0x01) || (fuel == 0x02)){
                PORTC = 0x60;
            }
            else{
                PORTC = 0x40;
            }
        }
        else if((fuel == 0x05) || (fuel == 0x06)){
            PORTC = 0x38;
        }
        else if((fuel == 0x07) || (fuel == 0x08) || (fuel == 0x09)){
            PORTC = 0x3C;
        }
        else if((fuel == 0x0A) || (fuel == 0x0B) || (fuel == 0x0C)){
            PORTC = 0x3E;
        }
        else if((fuel == 0x0D) || (fuel == 0x0E) || (fuel == 0x0F)){
            PORTC = 0x3F;
        }
    }
    return 1;
}