#include "Reply.h"

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
    return "Test";
}