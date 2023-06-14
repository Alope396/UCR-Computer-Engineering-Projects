#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct StringNode{
    string name;
    StringNode* next;
    StringNode* prev;
    StringNode(string name): name(name), next(nullptr), prev(nullptr) {}
};

int main(){
    string filename;
    int seats = 0;
    int start = 0;
    int k = 0;
    string name;
    ifstream inFS;
    StringNode *dummyHead = new StringNode("HEAD");
    StringNode *dummyTail = new StringNode("TAIL");
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
    //Opens file
    // cout<< "Input desired filename: " << endl;
    // cin>> filename;
    inFS.open("names1.txt");
    // inFS.open(filename);
    if(!inFS.is_open()){
        std::cout<< "Error opening file" << endl;
        return -1;
    }
    std::cout<< "Input number of seats" << endl;
    cin>> seats;
    //Reads in names and creates list
    for(unsigned int i = 0; i < seats; i++){
        getline(inFS, name);
        StringNode *newNode = new StringNode(name);
        dummyTail->prev->next = newNode;
        newNode->prev = dummyTail->prev;
        newNode->next = dummyTail;
        dummyTail->prev = newNode;
    }
    StringNode *head = dummyHead->next;
    StringNode *tail = dummyTail->prev;
    delete dummyHead;
    delete dummyTail;
    head->prev = tail;
    tail->next = head;
    //Finds starting seat
    std::cout<< "Input starting seat: (1 - " << seats << ")" << endl;
    cin>> start;
    int i = 0;
    StringNode *currNode = head;
    while(i < start - 1){
        currNode = currNode->next;
        i++;
    }
   std::cout<< "Starting seat: " << currNode->name << endl;
    //Sets how many seats to skip
    std::cout<< "Input number of seats to be skipped: " << endl;
    cin>> k;
    //Begins eliminating names
    i = 0;
    while(i < k){
        currNode = currNode->next;
        i++;
    }
        std::cout<< "First to die: " << currNode->name << endl;
    while(currNode != head && currNode != tail){
        i = 0;
        std::cout<< currNode->name << endl;
        StringNode *temp = currNode;
        std::cout<< temp->name << endl;
        if(temp = head){
            head = head->next;
        }
        else if (temp = tail){
            tail = tail->prev;
        }
        while(i < k + 1)
            currNode = currNode->next;
            i++;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        std::cout<< "Deleting " << temp->name << endl;
        delete temp;
    }
    cout<< "Winner: " << currNode->name << endl;
    return 0;
}