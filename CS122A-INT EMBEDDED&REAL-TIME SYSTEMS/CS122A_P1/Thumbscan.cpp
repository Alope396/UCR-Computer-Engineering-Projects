#include <wiringPi.h> //-lwiringPi
#include <iostream>
#include <signal.h>
#include "Adafruit_ADS1015.h"
#include "LiquidCrystal.h"
#include <python3.9/Python.h>
#include <fstream>
#include <string>
//To compile:g++ Thumbscan.cpp Adafruit_ADS1015.cpp LiquidCrystal.cpp -lwiringPi -I/usr/include/python3.9 -L$(python3.9-config --prefix)/lib $(python-config --ldflags)

using namespace std;

void tickDisplay();
void d_Menu();
void d_Options();

#define BUTTON 0
ofstream output;
ifstream input;

void cleanup(int signo){
    ClrLcd();
    digitalWrite(0, LOW);
    digitalWrite(1, LOW);
    printf("\n");
    exit(0);
}

enum D_STATES {D_Start, D_Prompt, D_Menu, D_Lock, D_Unlock, D_Options, D_Add, D_Remove, D_Logout} d_state;

string clear = " ";
int scan = 0;
int cursor = 0;
int unlock = 0;
int done = 0;
int stop = 0;
string buffer = "";
Adafruit_ADS1015 ads;

void tickDisplay(){
    int y = ads.readADC_Differential_2_3();
    int press = !digitalRead(BUTTON);
    switch(d_state){
        case D_Start:
            d_state = D_Prompt;
            break;
        case D_Prompt:
            // cout<< clear << endl;
            if(clear == "1"){
                d_state = D_Menu;
                ClrLcd();
                d_Menu();
                output.close();
                delay(1000);
                remove("read.txt");
                remove("write.txt");
                done = 0;
            }
            else{
                d_state = D_Prompt;
                if(!done){
                    output.open("read.txt");
                    output << "1";
                    output.close();
                    done = 1;
                }
                input.open("write.txt");
                getline(input, buffer);
                clear = buffer;
                input.close();
            }
            break;
        case D_Menu:
            delay(250);
            // cout<< clear << endl;
            if(cursor == 0 && press){
                d_state = D_Lock;
                cursor = 0;
                ClrLcd();
            }
            else if(cursor == 1 && press){
                d_state = D_Unlock;
                cursor = 0;
                ClrLcd();
            }
            // else if(cursor == 2 && press){
            //     d_state = D_Options;
            //     cursor = 0;
            //     ClrLcd();
            //     d_Options();
            // }
            else if(cursor == 2 && press){
                d_state = D_Logout;
                cursor = 0;
                ClrLcd();
            }
            else{
                d_state = D_Menu;
            }
            break;
        case D_Lock:
            d_state = D_Menu;
            digitalWrite(1,0);
            break;
        case D_Unlock:
            d_state = D_Menu;
            digitalWrite(1,1);
            break;
        case D_Options:
            delay(250);
            if(cursor == 0 && press){
                d_state = D_Add;
                cursor = 0;
            }
            else if(cursor == 1 && press){
                d_state = D_Remove;
                cursor = 0;
            }
            else if(cursor == 2 && press){
                d_state = D_Menu;
                cursor = 0;
                ClrLcd();
                d_Menu();
            }
            else{
                d_state = D_Options;
            }
            break;
        case D_Add:
            d_state = D_Options;
            break;
        case D_Remove:
            d_state = D_Options;
            break;
        case D_Logout:
            d_state = D_Prompt;
            break;
        default:
            break;
    }
    switch(d_state){
        case D_Start:
            break;
        case D_Prompt:
            lcdLoc(LINE1);
            typeln("     Welcome!!!");
            lcdLoc(LINE2);
            typeln("  Please Scan Your");
            lcdLoc(LINE3);
            typeln(" Thumb to Continue!");
            break;
        case D_Menu:
            clear = " ";
            if(y > 1200 && cursor > 0){
                cursor--;
                d_Menu();
            }
            else if(y < 400 && cursor < 2){
                cursor++;
                d_Menu();
            }
            else{
                cursor = cursor;
            }
            break;
        case D_Lock:
            lcdLoc(LINE2);
            if(unlock){
                typeln("      Locked!");
                unlock = 0;
            }
            else{
                typeln("  Already Locked!");
            }
            delay(2000);
            d_Menu();
            break;
        case D_Unlock:
            lcdLoc(LINE2);
            if(!unlock){
                typeln("     Unlocked!");
                unlock = 1;
            }
            else{
                typeln(" Already Unlocked!");
            }
            delay(2000);
            d_Menu();
            break;
        case D_Options:
            if(y > 1200 && cursor > 0){
                cursor--;
                d_Options();
            }
            else if(y < 400 && cursor < 2){
                cursor++;
                d_Options();
            }
            else{
                cursor = cursor;
            }
            break;
        case D_Add:
            break;
        case D_Remove:
            break;
        case D_Logout:
            stop = 1;
            break;
        default:
            break;
    }
}

enum T_STATES{T_Start, T_Lock, T_Unlock} t_state;

void tickToggleLock(){
    switch(t_state){
        case T_Start:
            t_state = T_Lock;
            break;
        case T_Lock:
            if(unlock){
                t_state = T_Unlock;
            }
            else{
                t_state = T_Lock;
            }
            break;
        case T_Unlock:
            if(unlock){
                t_state = T_Unlock;
            }
            else{
                t_state = T_Lock;
            }
            break;
        default:
            break;
    }
    switch(t_state){
        case T_Start:
            break;
        case T_Lock:
            digitalWrite(1,1);
            break;
        case T_Unlock:
            digitalWrite(1,0);
            break;
        default:
            break;
    }
}

void d_Menu(){
    if(cursor == 0){
        ClrLcd();
        lcdLoc(LINE1);
        typeln(">Lock");
        lcdLoc(LINE2);
        typeln("Unlock");
        lcdLoc(LINE3);
        // typeln("Options");
        // lcdLoc(LINE4);
        typeln("Logout");
    }
    else if(cursor == 1){
        ClrLcd();
        lcdLoc(LINE1);
        typeln("Lock");
        lcdLoc(LINE2);
        typeln(">Unlock");
        lcdLoc(LINE3);
        // typeln("Options");
        // lcdLoc(LINE4);
        typeln("Logout");
    }
    else if(cursor == 2){
        ClrLcd();
        lcdLoc(LINE1);
        typeln("Lock");
        lcdLoc(LINE2);
        typeln("Unlock");
        lcdLoc(LINE3);
        // typeln(">Options");
        // lcdLoc(LINE4);
        typeln(">Logout");
    }
    else if(cursor == 3){
        ClrLcd();
        lcdLoc(LINE1);
        typeln("Lock");
        lcdLoc(LINE2);
        typeln("Unlock");
        lcdLoc(LINE3);
        // typeln("Options");
        // lcdLoc(LINE4);
        typeln(">Logout");
    }
    else{
        return;
    }
}

void d_Options(){
    if(cursor == 0){
        ClrLcd();
        lcdLoc(LINE1);
        typeln(">Add");
        lcdLoc(LINE2);
        typeln("Remove");
        lcdLoc(LINE3);
        typeln("Back");
    }
    else if(cursor == 1){
        ClrLcd();
        lcdLoc(LINE1);
        typeln("Add");
        lcdLoc(LINE2);
        typeln(">Remove");
        lcdLoc(LINE3);
        typeln("Back");
    }
    else if(cursor == 2){
        ClrLcd();
        lcdLoc(LINE1);
        typeln("Add");
        lcdLoc(LINE2);
        typeln("Remove");
        lcdLoc(LINE3);
        typeln(">Back");
    }
    else{
        return;
    }
}

int main(){
    signal(SIGINT, cleanup);
    wiringPiSetup();
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pullUpDnControl(0, PUD_UP);
    ads.begin();    
    lcd_init();
    ClrLcd();

    while(1){
        tickDisplay();
        //tickToggleLock();
        if(stop){
            break;
        }
    }
    return 0;
}