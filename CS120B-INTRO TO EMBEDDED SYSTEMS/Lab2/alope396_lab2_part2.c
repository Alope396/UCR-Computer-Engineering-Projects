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
    DDRC = 0xFF; PORTC = 0x00;

    unsigned char cntavail = 0;
    unsigned char temp = 0x00;

    //A3 A2 A1 A0
    //8  4  2  1
    while (1) {
        temp = PINA;
        for(unsigned int i = 0; i < 4; i++){
            if((temp & 0x01) == 0x00){
                cntavail++;
            }
            temp = temp >> 1;
        }
        // if(PINA == 0x00){
        //     cntavail = 4;
        // }
        // else if(PINA == 0x01 || PINA == 0x02 || PINA == 0x04 || PINA == 0x08){
        //     cntavail = 3;
        // }
        // else if(PINA == 0x03 || PINA == 0x05 || PINA == 0x06 || PINA == 0x09 || PINA == 0x0A || PINA == 0x0C){
        //     cntavail = 2;
        // }
        // else if(PINA == 0x07 || PINA == 0x0B || PINA == 0x0D || PINA == 0x0E){
        //     cntavail = 1;
        // }
        // else{
        //     cntavail = 4;
        // }
        PORTC = cntavail;
        cntavail = 0;
    }
    return 1;
}