#include "BBoard.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

BBoard::BBoard(){
    title = "Default";
    current_user = nullptr;
}

BBoard::BBoard(const string & title){
    this->title = title;
    current_user = nullptr;
}

BBoard::~BBoard(){

}

bool BBoard::loadUsers(const string & filename){
    ifstream inFS;
    string userData = "";
    inFS.open(filename);
    if(!inFS.is_open()){
        cout<< "Error opening file" << filename << endl;
        return false;
    }
    while(inFS >> userData){

    }
}

bool BBoard::loadMessages(const string & filename){
    ifstream inFS;
    string messages = "";
    inFS.open(filename);
    if(!inFS.is_open()){
        cout<< "Error opening file: " << filename << endl;
        return false;
    }
    while(inFS >> messages){

    }
}

bool BBoard::saveMessages(const string & filename){

}

void BBoard::login(){
    string username = "";
    string password = "";
    cout<< "Enter your username ('Q' or 'q' to quit) : ";
    cin>> username;
    cout<< endl;
    while(username != "q" && username != "Q"){
        cout<< "Enter your password: ";
        cin>> password;
        cout<< endl;
        for(unsigned i = 0; i < user_list.size(); i++){
            if(user_list.at(i).checkLogin(username, password)){
                current_user = &user_list.at(i);
                cout<< endl << "Welcome back " << username << "!" << endl;
                cout<< endl;
                return;
            }
        }
        cout<< "Enter username: " << endl;
        cin>> username;
    }
    cout<< "Bye" << endl;
}

void BBoard::run(){
    string userInput = " ";
    if(current_user != nullptr){
        while(userInput != "q" || userInput != "Q"){
            cout<< "- Display Messages ('D' or 'd')" << endl;
            cout<< "- Add New Topic ('N' or 'n')" << endl;
            cout<< "- Add Reply to a Topic ('R' or 'r')" << endl;
            cout<< "- Quit ('Q' or 'q')" << endl;
            cout<< "Choose an action: ";
            if(userInput == "D" || userInput == "d"){
            // if(messageList.size() == 0){
            //         cout<< "Nothing to Display." << endl;
            //         cout<< endl;
            // }
            // else{
            //     for(unsigned i = 0; i < messageList.size(); i++){
            //         messages = messageList.at(i);
            //         cout<< "---------------------------------------------------------" << endl;
            //         cout<< "Message #" << i+1 << ": ";
            //         messages.display();
            //     }
            // cout<< "---------------------------------------------------------" << endl;
            // cout<< endl;
            }
            if(userInput == "N" || userInput == "n"){
                addMessage();
            }
            if(userInput == "R" || userInput == "r"){
                
            }
        }
    }
    return;
}