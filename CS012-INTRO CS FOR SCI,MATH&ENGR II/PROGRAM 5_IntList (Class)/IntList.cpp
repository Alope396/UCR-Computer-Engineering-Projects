#include <iostream>
#include <vector>

using namespace std;

#include "IntList.h"

IntList::IntList(){
    head = nullptr;
    tail = nullptr;
}

IntList::IntList(const IntList &cpy){
    if(cpy.head == nullptr){
        head = nullptr;
    }
    else{
        head = new IntNode(cpy.head->data);
        IntNode* currNode = head;
        IntNode* cpyCurr = cpy.head;
        while(cpyCurr->next != nullptr){
            currNode->next = new IntNode(cpyCurr->next->data);
            cpyCurr = cpyCurr->next;
            currNode = currNode->next;
        }
    }
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

void IntList::push_back(int value){
    IntNode* newNode = new IntNode(value);
    if(head != nullptr && tail != nullptr){
        tail->next = newNode;
        tail = newNode;
    }
    else{
        head = newNode;
        tail = newNode;
    }
}

void IntList::clear(){
    IntNode* currNode = head;
    while(currNode != nullptr){
        IntNode* nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }
    head = nullptr;
    tail = nullptr;
}

void IntList::selection_sort(){
    vector<int> nodeList;
    IntNode* currNode = head;
    if(currNode == nullptr){
        return;
    }
    while(currNode != nullptr){
        nodeList.push_back(currNode->data);
        currNode = currNode->next;
    }
    for(unsigned int i = 0; i < nodeList.size() - 1; i++){
        for(unsigned int j = i + 1; j < nodeList.size(); j++){
            int minVal = i;
            if(nodeList.at(j) < nodeList.at(i)){
                minVal = j;
            }
            int temp = nodeList.at(minVal);
            nodeList.at(minVal) = nodeList.at(i);
            nodeList.at(i) = temp;
        }
    }
    currNode = head;
    for(unsigned int i = 0; i < nodeList.size(); i++){
        currNode->data = nodeList.at(i);
        currNode = currNode->next;
    }
}

void IntList::insert_ordered(int value){
    IntNode* indexNode = head;
    IntNode* newNode = new IntNode(value);
    if(head == nullptr){
        head = newNode;
        tail = newNode;
        return;
    }
    else if(newNode->data >= tail->data){
        tail->next = newNode;
        tail = newNode;
        return;
    }
    else if(newNode->data <= indexNode->data){
        newNode->next = head;
        head = newNode;
        return;
    }
    IntNode* nextNode = indexNode->next;
    while(nextNode != nullptr){
        if(newNode->data < nextNode->data){
            indexNode->next = newNode;
            newNode->next = nextNode;
            nextNode = nullptr;
        }
        else{
            indexNode = indexNode->next;
            nextNode = nextNode->next;
        }
    }
}

void IntList::remove_duplicates(){
    IntNode* indexNode = head;
    while(indexNode != nullptr){
        IntNode* nextNode = indexNode->next;
        IntNode* lastNode = indexNode;
        while(nextNode != nullptr){
            if(indexNode->data == nextNode->data){
                IntNode* temp = nextNode;
                // cout<< "Removing " << temp->data << endl;
                if(temp == tail){
                    // cout<< "Tail was " << tail->data << endl;
                    tail = lastNode;
                    // cout<< "Tail is now " << tail->data << endl;
                    tail->next = nullptr;
                    delete temp;
                }
                else{
                    nextNode = nextNode->next;
                    lastNode->next = nextNode;
                    delete temp;
                }
            }
            else{
                lastNode = nextNode;
                nextNode = nextNode->next;
            }
        }
        indexNode = indexNode->next;
    }
}

IntList & IntList::operator=(const IntList &rhs){
    if(this != &rhs){
        this->head = nullptr;
        this->tail = nullptr;
        IntNode *temp = rhs.head;
        while(temp != nullptr){
            this->push_back(temp->data);
            temp = temp->next;
        }
    }
    return *this;
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
