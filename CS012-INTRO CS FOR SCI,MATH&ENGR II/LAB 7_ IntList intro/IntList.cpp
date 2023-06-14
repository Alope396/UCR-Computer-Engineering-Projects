#include <iostream>

using namespace std;

#include "IntList.h"

IntList::IntList(){
    head = nullptr;
    tail = nullptr;
}

IntList::~IntList(){
    IntNode* currNode = head;
    while(currNode != nullptr){
        IntNode* nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }
}

void IntList::push_front(int value){
    IntNode *newNode = new IntNode(value);
    if(head == nullptr){
        head = newNode;
        tail = newNode;
    }
    else{
        newNode->next = head;
        head = newNode;
    }
}

void IntList::pop_front(){
    IntNode* temp = head;
    if(head == nullptr){
        return;
    }
    else{
        head = temp->next;
        delete temp;
    }
}

bool IntList::empty() const{
    if(head == nullptr){
        return true;
    }
    else{
        return false;
    }
}

const int& IntList::front() const{
    return this->head->data;
}

const int& IntList::back() const{
    return this->tail->data;
}

ostream& operator<<(ostream & out, const IntList & list){
    IntNode *temp = list.head;
    if(temp != nullptr){
        out << temp->data;
        temp = temp->next;
    }
    while(temp != nullptr){
        out << " " << temp->data;
        temp = temp->next;
    }
    return out;
}
