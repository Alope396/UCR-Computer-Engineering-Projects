#include <string>
#include <iostream>

#include "Message.h"
using namespace std;

Message::Message(){
    author = "";
    subject = "";
    body = "";
    id = 0;
    vector<Message *> childList;
}

Message::~Message(){
    for(unsigned i = 0; i < childList.size(); i++){
        delete childList.at(i);
    }
}

Message::Message(const string & author, const string & subject, const string & body, unsigned id){
    this->author = author;
    this->subject = subject;
    this->body = body;
    this->id = id;
}

void Message::print(unsigned n) const{
    string indents = "";
    string body = this->body;

    for(unsigned i = 0; i < n; i++){
        indents = indents + "  ";
    }
    if(this->isReply()){
        cout<< endl;
    }
    cout<< indents << "Message #" << this->getID() << ": " << this->getSubject() << endl;
    cout<< indents << "from " << this->author << ": ";

    for(unsigned i = 0; i < body.size() - 1; i++){
        if(body.at(i) == '\n'){
            body.insert(i + 1, indents);
        }
    }
    cout<< body;
    
    if(childList.size() > 0){
        for(unsigned i = 0; i < childList.size(); i++){
            childList.at(i)->print(n+1);
        }
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