#include "Reply.h"
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

Reply::Reply(){
    author = "";
    subject = "";
    body = "";
}

Reply::Reply(const string & author, const string & subject, const string & body, unsigned id){
    this-> author = author;
    this-> subject = "Re: " + subject;
    this-> body = body;
    this-> id = id;
}

bool Reply::isReply() const{
    return true;
}

string Reply::toFormattedString() const{
    string inputString = "<begin_reply>";

    inputString = inputString + "\n" + ":id: " + to_string(this->id) + "\n" + ":subject: " + this->subject + "\n" + ":from: " + this->author;
    if(this->childList.size() > 0){
        inputString = inputString + "\n" + ":children: ";
        for(unsigned i = 0; i < childList.size(); i++){
            string x = "";
            x = to_string(childList.at(i)->getID());
            inputString = inputString + x;
            if(i < childList.size() -1){
                inputString = inputString + " ";
            }
        }
    }
    string str = this->body;
    str.erase(remove(str.end()-1, str.end(), '\n'), str.end());
    inputString = inputString + "\n" + ":body: " + str + "\n" + "<end>" + "\n";
    return inputString;
}