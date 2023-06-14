#include <string>
#include <iostream>

#include "Message.h"
using namespace std;

Message::Message(){
    author = "";
    subject = "";
    body = "";
    id = 0;
}

Message::Message(const string & author, const string & subject, const string & body, unsigned id){
    this->author = author;
    this->subject = subject;
    this->body = body;
    this->id = id;
}

void Message::print(unsigned n) const{
    if(n <= 1){
        cout<< childList.at(n);
    }
    else{
        cout<< childList.at(n);
        print(n-1);
    }
}

const string & Message::getSubject() const{
    return this->subject;
}

unsigned Message::getID() const{
    return this->id;
}

void Message::addChild(Message * newChild){
    childList.push_back(newChild);
}