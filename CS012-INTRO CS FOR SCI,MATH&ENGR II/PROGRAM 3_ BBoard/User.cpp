#include <iostream>
#include <string>

using namespace std;

#include "User.h"

User::User(){
    username = "";
    password = "";
}

User::User(const string & username, const string & password){
    this->username = username;
    this->password = password;
}

string User::getUsername() const{
    return this->username;
}

bool User::checkLogin(const string & username, const string & password){
    if(username != ""){
        if(this->username == username){
            if(this->password == password){
                return true;
            }
        }
    }
    return false;
}

bool User::changePassword(const string & oldPass, const string & newPass){
    if(checkLogin(this->username, oldPass)){
        this->password = newPass;
        return true;
    }
    return false;
}