#include <iostream>
#include <string>

using namespace std;

#include "IntVector.h"

bool testSize(IntVector* ptr, unsigned userS){
    if(ptr->size() == userS){
        return true;
    }
    else{
        return false;
    }
}

bool testCapacity(IntVector* ptr, unsigned userS){
    if(ptr->capacity() == userS){
        return true;
    }
    else{
        return false;
    }
}

bool testEmpty(IntVector* ptr, unsigned userS){
    if(userS != 0){
        if(ptr->empty() == false){
            return true;
        }
        else{
            return false;
        }
    }
    else if(userS == 0){
        if(ptr->empty() == true){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

int main(){
    IntVector* test1 = new IntVector();
    string userInput = "";
    unsigned userSize = 0;
    int userVal = 0;
    while(userInput != "Q" || userInput != "q"){
        cout<< "Which would you like to test?" << endl;
        cout<< "D - Default constructor" << endl;
        cout<< "P - Paramaterized constructor" << endl;
        cout<< "Q - Quit" << endl;
        cin>> userInput;
        if(userInput == "Q" || userInput == "q"){
            break;
        }
        else if(userInput == "D" || userInput == "d"){
            cout<< "Testing default constructor: " << endl;
            cout<< "Testing size(): " << endl;
            if(test1->size() == 0){
                cout<< "Test passed!" << endl;
            }
            else{
                cout<< "Test failed!" << endl;
            }
            cout<< "Testing capacity(): " << endl;
            if(test1->capacity() == 0){
                cout<< "Test passed!" << endl;
            }
            else{
                cout<< "Test failed!" << endl;
            }
            cout<< "Testing empty() on empty array: " << endl;
            if(test1->empty() == true){
                cout<< "Test passed!" << endl;
            }
            else{
                cout<< "Test failed!" << endl;
            }
            test1->~IntVector();
        }
        else if(userInput == "P" || userInput == "p"){
            cout<<"Please enter the parameters (int size, int value): " << endl;
            cin>> userSize;
            cin>> userVal;
            IntVector* test2 = new IntVector(userSize, userVal);
            cout<< "Testing size(): " << endl;
            if(testSize(test2, userSize)){
                cout<< "Test passed!" << endl;
            }
            else{
                cout<< "Test failed!" << endl;
            }
            cout<< "Testing capacity(): " << endl;
            if(testCapacity(test2, userSize)){
                cout<< "Test passed!" << endl;
            }
            else{
                cout<< "Test failed!" << endl;
            }
            cout<< "Testing empty() on a nonempty array: " << endl;
            if(!test2->empty()){
                cout<< "Test passed!" << endl;
            }
            else{
                cout<< "Test failed!" << endl;
            }
            cout<< "Testing at(1): " << endl;
            if(1 <= userSize){
                if(test2->at(1) == userVal)
                {
                    cout<< "Test passed!" << endl;
                }
                else
                {
                    cout<< "Test failed!" << endl;
                }
            }
            else if(1 >= userSize){
                test2->at(1);
            }
            cout<< "Testing front(): " << endl;
            if(test2->front() == userVal){
                cout<< "Test passed!" << endl;
            }
            else{
                cout<< "Test failed!" << endl;
            }
            cout<< "Testing back(): " << endl;
            if(test2->back() == userVal){
                cout<< "Test passed!" << endl;
            }
            else{
                cout<< "Test failed!" << endl;
            }
            test2->~IntVector();
            cout<< "Testing deconstructor: " << endl;
            if(test2->front() == userVal){
                cout<< "Test failed!" << endl;
                cout<< test2->front() << endl;
            }
            else{
                cout<< "Test passed!" << endl;
            }
        }
    }
    return 0;
}