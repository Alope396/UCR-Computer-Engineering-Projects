#include <iostream>
#include "IntList.h"
using namespace std;

int main(){
    IntList newList;
    bool check;
    check = newList.empty();
    if(check == true){
        cout<<"empty"<<endl;
    }
    newList.push_back(1);
    newList.push_back(2);
    newList.push_back(3);
    cout<< newList << endl;
    check = newList.empty();
    if(check == false){
        cout<<"not empty"<<endl;
    }
    newList.printReverse();
    cout<< endl;

    IntList list;
    check = list.empty();
    if(check == true){
        cout<<"empty"<<endl;
    }
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    cout<< list << endl;
    check = list.empty();
    if(check == false){
        cout<<"not empty"<<endl;
    }
    list.printReverse();
    cout<< endl;
    list.pop_back();
    list.pop_front();
    cout<< list;
    check = list.empty();
    if(check == false){
        cout<<"not empty" << endl;
    }
    return 0;
};
