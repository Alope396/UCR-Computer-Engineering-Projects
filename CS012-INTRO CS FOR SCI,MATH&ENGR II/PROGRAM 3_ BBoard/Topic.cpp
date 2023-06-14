#include "Topic.h"
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

Topic::Topic(){
    author = "";
    subject = "";
    body = "";
    id = 0;
}

Topic::Topic(const string & author, const string & subject, const string & body, unsigned id){
    this->author = author;
    this->subject = subject;
    this->body = body;
    this->id = id;
}

bool Topic::isReply() const{
    return false;
}

string Topic::toFormattedString() const{
    string inputString = "<begin_topic>";

    inputString = inputString + "\n" + ":id: " + to_string(this->id) + "\n" + ":subject: " + this->subject + "\n" + ":from: " + this->author;
    if (this->childList.size() > 0) {
        inputString = inputString + "\n" + ":children: ";
        for (unsigned int i = 0; i < childList.size(); i++) {
            string x = to_string(childList.at(i)->getID());
            inputString = inputString + x;
            if (i < childList.size()-1) {
                inputString = inputString + " ";
            }
        }
    }
    string str = this->body;
    str.erase(remove(str.end()-1, str.end(), '\n'), str.end());
    inputString = inputString + "\n" + ":body: " + str + "\n" + "<end>" + "\n";
    
    return inputString;
}