#include "IntList.h"
#include <iostream>

using namespace std;

IntList::IntList(): dummyHead(new IntNode(-1)), dummyTail(new IntNode(-1)) {
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
}

IntList::~IntList(){
    IntNode *currNode = dummyHead->next;
    while(currNode != dummyTail){
        IntNode *temp = currNode;
        currNode = currNode->next;
        delete temp;
    }
}

void IntList::push_front(int value){
    IntNode *newNode = new IntNode(value);
    dummyHead->next->prev = newNode;
    newNode->next = dummyHead->next;
    dummyHead->next = newNode;
    newNode->prev = dummyHead;
}

void IntList::pop_front(){
    if(!empty()){
        IntNode *temp = dummyHead->next;
        dummyHead->next = dummyHead->next->next;
        dummyHead->next->prev = dummyHead;
        delete temp;
    }
    else{
        cout<< "List is empty." << endl;
    }
}

void IntList::push_back(int value){
    IntNode *newNode = new IntNode(value);
    IntNode *temp = dummyTail->prev;
    newNode->next = dummyTail;
    temp->next = newNode;
    dummyTail->prev = newNode;
    newNode->prev = temp;
}

void IntList::pop_back(){
    if(!empty()){
        IntNode *temp = dummyTail->prev;
        dummyTail->prev = dummyTail->prev->prev;
        dummyTail->prev->next = dummyTail;
        delete temp;
    }
    else{
        cout<< "List is empty." << endl;
    }
}

bool IntList::empty() const{
    if(dummyHead->next == dummyTail){
        return true;
    }
    else{
        return false;
    }
}

ostream &operator<<(ostream &out, const IntList &rhs){
    IntNode *currNode = rhs.dummyHead->next;
    while(currNode != rhs.dummyTail){
        out<< currNode->data;
        if(currNode != rhs.dummyTail->prev){
            out<< " ";
        }
        currNode = currNode->next;
    }
    return out;
}

void IntList::printReverse() const{
    IntNode *currNode = dummyTail->prev;
    if(currNode == dummyHead){
        return;
    }
    while(currNode != dummyHead->next){
        cout<< currNode->data << " ";
        currNode = currNode->prev;
    }
    cout<< currNode->data;
}