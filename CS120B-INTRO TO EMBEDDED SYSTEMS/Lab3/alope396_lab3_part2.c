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

    unsigned char temp = PINA;

    while (1) {
        temp = PINA & 0x0F;
        if(temp <= 0x04){
            if((temp == 0x03) || (temp == 0x04)){
                PORTC = 0x70;
            }
            else{
                PORTC = 0x40;
            }
        }
        else if((temp == 0x05) || (temp == 0x06)){
            PORTC = 0x38;
        }
        else if((temp == 0x07) || (temp == 0x08) || (temp == 0x09)){
            PORTC = 0x3C;
        }
        else if((temp == 0x0A) || (temp == 0x0B) || (temp == 0x0C)){
            PORTC = 0x3E;
        }
        else if((temp == 0x0D) || (temp == 0x0E) || (temp == 0x0F)){
            PORTC = 0x3F;
        }
    }
    return 1;
}