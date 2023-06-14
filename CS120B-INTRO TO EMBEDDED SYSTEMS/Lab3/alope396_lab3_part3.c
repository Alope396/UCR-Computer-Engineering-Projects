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
    unsigned char temp2 = PINA;
    unsigned char fuel = 0x00;
    unsigned char system = 0x00;

    while (1) {
        temp = PINA & 0x0F;
        if(temp <= 0x04){
            if((temp == 0x03) || (temp == 0x04)){
                fuel = 0x70;
            }
            else{
                fuel = 0x40;
            }
        }
        else if((temp == 0x05) || (temp == 0x06)){
            fuel = 0x38;
        }
        else if((temp == 0x07) || (temp == 0x08) || (temp == 0x09)){
            fuel = 0x3C;
        }
        else if((temp == 0x0A) || (temp == 0x0B) || (temp == 0x0C)){
            fuel = 0x3E;
        }
        else if((temp == 0x0D) || (temp == 0x0E) || (temp == 0x0F)){
            fuel = 0x3F;
        }
        temp2 = PINA & 0xF0;
        if(temp2 == 0x30){
            PORTC = (fuel | 0x80);
        }
        else{
            PORTC = fuel;
        }
    }
    return 1;
}