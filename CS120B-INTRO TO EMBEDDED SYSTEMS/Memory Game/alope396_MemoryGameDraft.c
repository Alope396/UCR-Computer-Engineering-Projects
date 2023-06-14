/*      Author: lab
 *  Partner(s) Name: 
 *      Lab Section:
 *      Assignment: Lab #  Exercise #
 *      Exercise Description: [optional - include for your own benefit]
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 * 
 *      Demo Link:https://youtu.be/FyAJhgkZICk
 */
#include <avr/io.h>
#include <avr/eeprom.h>
#ifdef _SIMULATE_
#include <avr/interrupt.h>
#include "simAVRHeader.h"
#endif
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

volatile unsigned char TimerFlag = 0;
void TimerISR(){TimerFlag = 1;}
void TimerSet(unsigned long M){
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}
void TimerOn(){
    TCCR1B = 0x0B;
    OCR1A = 125;
    TIMSK1 = 0x02;
    TCNT1 = 0;
    _avr_timer_cntcurr = _avr_timer_M;
    SREG |= 0x80;
}
void TimerOff(){
    TCCR1B = 0x00;
}
ISR(TIMER1_COMPA_vect){
    _avr_timer_cntcurr--;
    if(_avr_timer_cntcurr == 0){
        TimerISR();
        _avr_timer_cntcurr = _avr_timer_M;
    }
}

typedef struct task{
    signed char state;
    unsigned long int period;
    unsigned long int elapsedTime;
    int (*TickFct)(int);
}task;

void ADC_init(){
    ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<< ADATE);
}

void clearLED(){
    PORTA = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
}

void setLED(unsigned char x, unsigned char y){
    if(x == 0){
        PORTD = y;
    }
    else if(x == 1){
        PORTA = y;
    }
    else if(x == 2){
        PORTC = y;
    }
    else{
        return;
    }
}


uint8_t high_score;

void displayHighScore(){
    high_score = eeprom_read_byte((uint8_t*)46);
    PORTC = PORTC | high_score;
    return;
}


unsigned char c1[8] = {0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};
unsigned char c2[8] = {0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00};
unsigned char o1[8] = {0xFF, 0x31, 0x42, 0x11, 0x80, 0x04, 0x40, 0x81};
unsigned char o2[8] = {0xFF, 0x42, 0x80, 0x40, 0x31, 0x81, 0x11, 0x40};
unsigned char o3[8] = {0xFF, 0x40, 0x31, 0x42, 0x81, 0x04, 0x80, 0x11};

unsigned char turn = 0;
unsigned char incorrect = 0;
unsigned char pass = 0;
unsigned char arr_counter = 0;
unsigned char i = 0;
unsigned char j = 0;
unsigned char lives = 3;
unsigned char level = 1;
unsigned char toggle_timer = 0;
unsigned char timer = 0;
unsigned char game[9] = {0,1,2,0,1,2,0,1,2};

enum D_STATE{START, WAIT, DISPLAY, FAIL, CORRECT, GAMEOVER, WIN};
int Tick_DisplayLED(int state){
    unsigned char size = (sizeof(game)/sizeof(game[0]));
    unsigned char button = (~PINB & 0x01);
    unsigned char score;
    switch(state){
        case START:
            if(button == 0x01){
                state = WAIT;
            }
            else{
                state = START;
            }
            break;
        case WAIT:
            if(lives == 1){
                PORTB = 0x02;
            }
            else if(lives == 2){
                PORTB = 0x06;
            }
            else if(lives == 3){
                PORTB = 0x0E;
            }
            if(turn == 0 && incorrect == 0 && pass == 0 && lives > 0){
                state = DISPLAY;
            }
            else if(lives == 0){
                i = 0;
                state = GAMEOVER;
            }
            else if(incorrect == 1){
                i = 0;
                state = FAIL;
            }
            else if(pass == 1){
                i = 0;
                score++;
                state = CORRECT;
            }
            else{
                state = WAIT;
            }
            break;
        case DISPLAY:
            if(j < 10){
                j++;
            }
            else{
                if(i < level){
                    state = DISPLAY;
                    clearLED();
                    setLED(game[i], 0xFF);
                    i++;
                }
                else{
                    state = WAIT;
                    arr_counter = 0;
                    clearLED();
                    i = 0;
                    turn = 1;
                }
                j = 0;
            }
            toggle_timer = 0;
            break;
        case FAIL:
            if(j < 8){
                if(j%2 == 0){
                    setLED(game[arr_counter], 0xFF);
                }
                else{
                    setLED(game[arr_counter], 0x00);
                }
                j++;
            }
            else{
                j = 0;
                incorrect = 0;
                lives--;
                state = WAIT;
            }
            toggle_timer = 0;
            break;
        case CORRECT:
            if(j < 8){
                if(i < 8){
                    setLED(0, c1[i]);
                    i++;
                }
                else{
                    i = 0;
                }
                j++;
            }
            else if(j < 17){
                if(i < 8){
                    setLED(0, c2[i]);
                    setLED(1, c1[i]);
                    i++;
                }
                else{
                    i = 0;
                }
                j++;
            }
            else if(j < 26){
                if(i < 8){
                    setLED(1, c2[i]);
                    setLED(2, c1[i]);
                    i++;
                }
                else{
                    i = 0;
                }
                j++;
            }
            else{
                j = 0;
                i = 0;
                turn = 0;
                clearLED();
                if(score < 9){
                    state = WAIT;
                    level++;
                    pass = 0;
                }
                else{
                    state = WIN;
                }
            }
            toggle_timer = 0;
            break;
        case GAMEOVER:
            if(j < 8){
                PORTA = o1[j];
                PORTC = o2[j];
                PORTD = o3[j];
                PORTB = 0x00;
                j++;
            }
            else{
                clearLED();
                j = 0;
                state = START;
            }
            toggle_timer = 0;
            break;
        case WIN:
            if(j < 8){
                if(j%2 == 0){
                    setLED(game[0], 0xFF);
                    setLED(game[1], 0xFF);
                    setLED(game[2], 0xFF);
                }
                else{
                    clearLED();
                }
                j++;
            }
            else{
                state = START;
            }
            toggle_timer = 0;
            break;
        default:
            break;
    }
    switch(state){
        case START:
            score = 0;
            lives = 3;
            clearLED();
            break;
        default:
            break;
    }
    return state;
}

unsigned char pos = 1;
enum S_STATES{INIT, SELECT, CHECK};
int Tick_Select(int state){
    unsigned short x = ADC;
    unsigned char press = ~PINB & 0x01;
    unsigned char size = (sizeof(game)/sizeof(game[0]));
    unsigned char choice = 0;
    switch(state){
        case INIT:
            state = SELECT;
            break;
        case SELECT:
            if(turn == 1){
                toggle_timer = 1;
                if(x < 400 && pos > 0){
                    pos--;
                }
                else if(x > 600 && pos < 2){
                    pos++;
                }
                else if(press == 0x01){
                    state == CHECK;
                }
                else if(arr_counter == size && incorrect == 0){
                    pass = 1;
                }
                clearLED();
                setLED(pos, 0xFF);
            }
            else{
                state = SELECT;
            }
            break;
        case CHECK:
            if(pos == game[arr_counter]){
                if(arr_counter < level){
                    arr_counter++;
                }
                else{
                    state = SELECT;
                    pass = 1;
                    turn = 0;
                }
            }
            else{
                incorrect = 1;
                turn = 0;
            }
            PORTB == 0x00;
            state = SELECT;
            break;
        default:
            break;
    }
    switch(state){
        case INIT:
            break;
        case SELECT:
            break;
        case CHECK:
            break;
        default:
            break;
    }
    return state;
}

enum T_STATES{T_Start, T_On, T_Off};
int Tick_Timer(int state){
    switch(state){
        case T_Start:
            if(toggle_timer == 0){
                state = T_Start;
            }
            else{
                state = T_On;
            }
            break;
        case T_On:
            if(toggle_timer == 0){
                state = T_Off;
            }
            else{
                state = T_On;
            }
            break;
        case T_Off:
            if(toggle_timer == 0){
                state = T_Off;
            }
            else{
                state = T_On;
            }
            break;
    }
    switch(state){
        case T_Start:
            break;
        case T_On:
            timer++;
            break;
        case T_Off:
            break;
        default:
            break;
    }
    return state;
}

int main(void) {
    DDRA = 0xFE; PORTA = 0x00;
    DDRB = 0x0E; PORTB = 0x01;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;

    static task D_Task, S_Task;
    task *tasks[] = {&D_Task, &S_Task};
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

    const char start = 0;

    D_Task.state = start;
    D_Task.period = 50;
    D_Task.elapsedTime = D_Task.period;
    D_Task.TickFct = &Tick_DisplayLED;

    S_Task.state = start;
    S_Task.period = 200;
    S_Task.elapsedTime = S_Task.period;
    S_Task.TickFct = &Tick_Select;
    
    T_Task.state = start;
    T_Task.period = 1000;
    T_Task.elapsedTime = T_Task.period;
    T_Task.TickFct = &Tick_Timer;

    TimerSet(50);
    TimerOn();
    clearLED();
    ADC_init();

    unsigned short i;

    while (1) {
        for(i = 0; i < numTasks; i++){
            if(tasks[i]->elapsedTime == tasks[i]->period){
                tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
                tasks[i]->elapsedTime = 0;
            }
            tasks[i]->elapsedTime += 50;
        }
        while(!TimerFlag){}
            TimerFlag = 0;
    }
    return 0;
}