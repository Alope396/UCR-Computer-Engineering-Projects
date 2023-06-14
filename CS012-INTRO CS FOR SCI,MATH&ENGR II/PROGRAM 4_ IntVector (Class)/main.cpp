#include <iostream>
#include <vector>

using namespace std;

#include "IntVector.h"

void Print(IntVector x){
    for(unsigned i = 0; i < x.size(); i++){
        cout<< x.at(i) << " ";
    }
}

int main(){
    IntVector test1;
    IntVector test2(5, 4);
    
    test1.push_back(6);
    cout<< "Testing push_back(6), expecting: 6, returned: ";
    Print(test1);
    cout<< endl;
    cout<< "Testing size(), expecting 1, returned: " << test1.size() << endl;
    cout<< "Testing capacity(), expecting 1, returned: " << test1.capacity() << endl;
    cout<< "Testing empty() on nonempty array: ";
    if(test1.empty()){
        cout<< "Test failed!" << endl;
    }
    else{
        cout<< "Test passed" << endl;
    }
    cout<< "Testing at(0), expecting 1, returned: " << test1.at(0) << endl;
    test1.insert(0, 1);
    cout<< "Testing insert(0, 1), expecting 1 6, returneed: ";
    Print(test1);
    cout<< endl;
    cout<< "Testing front(), expecting 1, returned: " << test1.front() << endl;
    cout<< "Testing back(), expecting 6, returned: " << test1.back() << endl;
    cout<< "Testing assign(10, 3), expecting 3 3 3 3 3 3 3 3 3 3, returned: ";
    test1.assign(10 , 3);
    Print(test1);
    cout<< endl;
    cout<< "Testing pop_back(), expecting 3 3 3 3 3 3 3 3 3, returned ";
    test1.pop_back();
    Print(test1);
    cout<< endl;
    cout<< "Testing resize(2), expecting 3 3, returned: ";
    test1.resize(2);
    Print(test1);
    cout<< endl;
    cout<< "Testing resize(4, 5), expecting 3 3 5 5, returned: ";
    test1.resize(4,5);
    Print(test1);
    cout<< endl;
    test1.reserve(10);
    cout<< "Testing reserve(10), expecting capacity = 10, returned capacity = " << test1.capacity() << endl;
    test1.assign(3, 1);
    cout<< "Testing assign(3, 1), expecting 1 1 1, returned: ";
    Print(test1);
    cout<< endl;
    test1.erase(1);
    cout<< "Testing erase(1), expecting 1 1, returned: ";
    Print(test1);
    cout<< endl;
    test1.clear();
    cout<< "Testing clear(), expecting size = 0; returned size = " << test1.size() << endl;
    test1.~IntVector();
    
    test2.push_back(6);
    cout<< "Testing push_back(), expecting: 4 4 4 4 4 6, returned: ";
    Print(test2);
    cout<< endl;
    cout<< "Testing size(), expecting 6, returned: " << test2.size() << endl;
    cout<< "Testing capacity(), expecting 10, returned: " << test2.capacity() << endl;
    cout<< "Testing empty() on nonempty array: ";
    if(test2.empty()){
        cout<< "Test failed!" << endl;
    }
    else{
        cout<< "Test passed" << endl;
    }
    cout<< "Testing at(5), expecting 6, returned: " << test2.at(5) << endl;
    test2.insert(2, 1);
    cout<< "Testing insert(2, 1), expecting 4 1 4 4 4 4 6, returneed: ";
    Print(test2);
    cout<< endl;
    cout<< "Testing front(), expecting 4, returned: " << test2.front() << endl;
    cout<< "Testing back(), expecting 6, returned: " << test2.back() << endl;
    cout<< "Testing assign(10, 3), expecting 3 3 3 3 3 3 3 3 3 3, returned: ";
    test2.assign(10 , 3);
    Print(test2);
    cout<< endl;
    cout<< "Testing pop_back(), expecting 3 3 3 3 3 3 3 3 3, returned ";
    test2.pop_back();
    Print(test2);
    cout<< endl;
    cout<< "Testing resize(2), expecting 3 3, returned: ";
    test2.resize(2);
    Print(test2);
    cout<< endl;
    cout<< "Testing resize(4, 5), expecting 3 3 5 5, returned: ";
    test2.resize(4,5);
    Print(test2);
    cout<< endl;
    test2.reserve(10);
    cout<< "Testing reserve(10), expecting capacity = 10, returned capacity = " << test2.capacity() << endl;
    test2.assign(3, 1);
    cout<< "Testing assign(3, 1), expecting 1 1 1, returned: ";
    Print(test2);
    cout<< endl;
    test2.erase(1);
    cout<< "Testing erase(1), expecting 1 1, returned: ";
    Print(test2);
    cout<< endl;
    test2.clear();
    cout<< "Testing clear(), expecting size = 0; returned size = " << test2.size() << endl;
    test2.~IntVector();
    return 0;
}