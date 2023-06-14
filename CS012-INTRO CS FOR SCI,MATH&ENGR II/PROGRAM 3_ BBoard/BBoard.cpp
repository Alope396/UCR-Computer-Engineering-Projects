#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

#include "BBoard.h"
#include "Topic.h"
#include "Reply.h"

BBoard::BBoard(){
    title = "Welcome to CS12 Bulletin Board";
    current_user = nullptr;
}

BBoard::~BBoard(){
    for(int i = message_list.size() - 1; i > 0; i--){
        if(!message_list.at(i)->isReply()){
            delete message_list.at(i);
        }
    }
}

BBoard::BBoard(const string & title){
   this->title = title;
   current_user = nullptr;
}

bool BBoard::loadUsers(const string &filename){
   bool check = false;
   ifstream inFS;
   vector<string> userInfo;
   string file = "";
   string info = "";
   string name = "";
   string password = "";
   file = filename;
   inFS.open(file);
   if(inFS.is_open()){
      while(inFS >> info){
         if(info != "end"){
            userInfo.push_back(info);
         }
      }
      for(unsigned int i = 0; i < userInfo.size(); i++){
         name = userInfo.at(i);
         password = userInfo.at(i+1);
         user_list.push_back(User(name, password));
         i = i + 1;
         check = true;
      }
   }
      return check;
}

bool BBoard::loadMessages(const string & filename){
    ifstream inFS;
    vector<int> children;
    vector<int> parents;
    string file = filename;
    string messages = "";
    string author = "";
    string subject = "";
    string body = "";
    string cID = "";
    string pID = "";
    int childID = 0;
    int id = 0;
    unsigned int counter = 0;
    
    inFS.open(file);
    if(inFS.is_open()){
        inFS >> counter;
        for(unsigned i = 0; i < counter; i++){
            inFS >> messages;
            if(messages == "<begin_topic>"){
                inFS >> messages;
                inFS >> id;
                inFS >> messages;
                inFS.get();
                getline(inFS, subject);
                inFS >> messages;
                inFS >> author;
                inFS >> messages;
                if(messages == ":children:"){
                    int temp = 0;
                    getline(inFS, cID);
                    stringstream SS(cID);
                    while(SS >> cID){
                        temp += 1;
                        children.push_back(childID);
                    }
                    parents.push_back(i+1);
                    parents.push_back(temp);
                    inFS >> messages;
                }
                inFS.get();
                getline(inFS, body, '<');
                Topic *newTopic = new Topic(author, subject, body, id);
                message_list.push_back(newTopic);
                inFS>> messages;
        }
        else if(messages == "<begin_reply>"){
            inFS >> messages;
            inFS >> id;
            inFS >> messages;
            inFS >> messages;
            inFS.get();
            getline(inFS, subject);
            inFS >> messages;
            inFS >> author;
            inFS >> messages;
            if(messages == ":children:"){
                int temp = 0;
                getline(inFS, cID);
                stringstream SS(cID);
                while(SS >> cID){
                    children.push_back(childID);
                    temp++;
                }
                parents.push_back(i+1);
                parents.push_back(temp);
                inFS >> messages;
            }
            inFS.get();
            getline(inFS, body, '<');
            Reply *newReply = new Reply(author, subject, body, id);
            message_list.push_back(newReply);
            inFS>> messages;
        }
        }
        unsigned i = 0;
        unsigned temp = 0;
        unsigned x = 1;
        for(unsigned j = 0; j < parents.size(); j = j + 2){
            temp = 0;
            temp = temp + parents.at(j);
            while(i < temp){
                message_list.at(parents.at(j) - 1)->addChild(message_list.at(children.at(i)+ 1));
                i++;
            }
            x++;
        }
    }
    inFS.close();
    return true;
}

bool BBoard::saveMessages(const string & filename){
    ofstream oFS(filename);
    string out;
    oFS<< message_list.size() << endl;
    for(unsigned i = 0; i < message_list.size(); i++){
        out = message_list.at(i)->toFormattedString();
        oFS<< out;
    }
    return true;
}

void BBoard::login()
{
    string user;
    string pass;
    cout<< "Welcome to " << this->title << endl;
    string username = "";
    string password = "";
    cout<< "Enter your username ('Q' or 'q' to quit): ";
    cin>> username;
    while(username != "q" && username != "Q"){
        cout<< "Enter your password: ";
        cin>> password;
        for(unsigned i = 0; i < user_list.size(); i++){
            if(user_list.at(i).checkLogin(username, password)){
                current_user = &user_list.at(i);
                cout<< endl << "Welcome back " << username << "!" << endl;
                cout<< endl;
                return;
            }
        }
        cout << "Invalid Username or Password!" << endl;
        cout << endl;
        cout<< "Enter your username ('Q' or 'q' to quit): ";
        cin>> username;
    }
    cout<< "Bye!" << endl;
}

void BBoard::run(){
    char userInput = ' ';
    if(current_user != nullptr){
        cout<< "Menu" << endl;
        cout<< "- Display Messages ('D' or 'd')" << endl;
        cout<< "- Add New Topic ('N' or 'n')" << endl;
        cout<< "- Add Reply to a Topic ('R' or 'r')" << endl;
        cout<< "- Quit ('Q' or 'q')" << endl;
        cout<< "Choose an action: ";
        cin>> userInput;
        if(userInput == 'Q' || userInput == 'q'){
            cout<< "Bye!" << endl;
            return;
        }
        if(userInput == 'D' || userInput == 'd'){
            if(message_list.size() == 0){
                cout<< endl;
                cout<< "Nothing to Display." << endl;
            }
            else{
                cout<< endl;
                cout<< "---------------------------------------------------------" << endl;
                for(unsigned i = 0; i < message_list.size(); i++){
                    if(!message_list.at(i)->isReply()){
                        message_list.at(i)->print(0);
                        cout<< "---------------------------------------------------------" << endl;
                    }
                }
            }
            cout<< endl;
            run();
        }
        if(userInput == 'N' || userInput == 'n'){
            cin.ignore();
            string subject = "";
            string body = "";
            string x = "";
            cout<< "Enter Subject: ";
            getline(cin, subject);
            subject = x + subject;
            cout<< "Enter Body: " << endl;
            getline(cin, x);
            while(x != ""){
                body = body + x + "\n";
                getline(cin, x);
            }
            string userName = current_user->getUsername();
            Topic *newTopic = new Topic(current_user->getUsername(), subject, body, message_list.size()+1);
            message_list.push_back(newTopic);
            run();
        }
        if(userInput == 'R' || userInput == 'r'){
            cout << "Enter Message ID (-1 for Menu): ";
            int msgID;
            cin >> msgID;
            while (msgID > int(message_list.size())) {
                cout << "Invalid Message ID!!" << endl;
                cin >> msgID;
            }
            if (msgID < 0) {
            }
                cout << "Enter Body: ";
                string replyBody = "";
                string temp = "";
                cin.ignore();
                getline(cin, temp);
                while (temp != "") {
                    replyBody = replyBody + temp + "\n";
                    getline(cin,temp);
                }
                Reply *newReply = new Reply(current_user->getUsername(), message_list.at(msgID-1)->getSubject(), replyBody, message_list.size()+1);
                message_list.push_back(newReply);
                message_list.at(msgID-1)->addChild(newReply);
            run();
        }
    }
}

// void BBoard::addMessage()
// {
//    string newBody;
//    string newSubject;
//    unsigned temp = messageList.size();
//    cout<< "Enter Subject: " << endl;
//    cin.ignore();
//    getline(cin, newSubject);
//    cout<< "Enter Body: " << endl;
//    getline(cin, newBody);
//    messageList.push_back(Message(currentUser.getUsername(), newSubject, newBody));
//    if(messageList.size() > temp)
//    {
//       cout<< "Message Recorded!" << endl;
//       cout<< endl;
//    }
// }
