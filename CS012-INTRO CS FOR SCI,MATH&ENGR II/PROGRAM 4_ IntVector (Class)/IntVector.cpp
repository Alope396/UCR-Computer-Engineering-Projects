#include <iostream>
#include <stdexcept>

using namespace std;

#include "IntVector.h"

IntVector::IntVector(){
    sz = 0;
    cap = 0;
    data = nullptr;
}

IntVector::IntVector(unsigned size, int value){
    sz = size;
    cap = size;
    data = new int [size];
    for(unsigned int i =0; i < size; i++){
        data[i] = value;
    }
}

IntVector::~IntVector(){
    delete[] data;
}

unsigned IntVector::size() const{
    return sz;
}

unsigned IntVector::capacity() const{
    return cap;
}

bool IntVector::empty() const{
    if(sz == 0){
        return true;
    }
    else{
        return false;
    }
}

const int& IntVector::at(unsigned index) const{
    if(index >= sz){
        throw out_of_range("IntVector::at_range_check");
    }
    else{
        return data[index];
    }
}

int & IntVector::at(unsigned index){
    if(index >= sz){
        throw out_of_range("IntVector::at_range_check");
    }
    else{
        return data[index];
    }
}

void IntVector::insert(unsigned index, int value){
    if(index > sz){
        throw out_of_range("IntVector::insert_range_check");
    }
    if(sz >= cap){
        expand();
    }
    sz++;
    for(unsigned int i = sz - 1; i > index; i--){
        data[i] = data[i - 1];
    }
    data[index] = value;
}

void IntVector::erase(unsigned index){
    if(index >= sz){
        throw out_of_range("IntVector::erase_range_check");
    }
    data[index] = 0;
    for(unsigned int i = index; i < sz; i++){
        data[i] = data[i+1];
    }
    sz -= 1;
}

const int& IntVector::front() const{
    return data[0];
}

int & IntVector::front(){
    return data[0];
}

const int& IntVector::back() const{
    return data[sz-1];
}

int & IntVector::back(){
    return data[sz-1];
}

void IntVector::assign(unsigned n, int value){
    for(unsigned int i = 0; i < sz; i++){
        data[i] = 0;
    }
    if(n > cap){
        if(cap * 2 > n){
            expand();
        }
        else{
            expand(n-cap);
        }
    }
    sz = n;
    for(unsigned int i = 0; i < sz; i++){
        data[i] = value;
    }
}

void IntVector::push_back(int value){
    if(sz >= cap){
        expand();
    }
    sz += 1;
    data[sz-1] = value;
}

void IntVector::pop_back(){
    sz -= 1;
}

void IntVector::clear(){
    sz = 0;
}

void IntVector::resize(unsigned size, int value){
    if(size < sz){
        sz = size;
    }
    else if(size > sz){
        int index = sz;
        if(size >= cap){
            if(sz * 2 > size){
                expand();
            }
            else{
                expand(size - cap);
            }
        }
        sz = size;
        for(unsigned int i = index; i < sz; i++){
            data[i] = value;
        }
    }
}

void IntVector::reserve(unsigned n){
    if(n > cap){
        cap = n;
    }
}

void IntVector::expand(){
    if(cap == 0){
        cap = 1;
    }
    else{
        cap = cap * 2;
    }
        int* expand = data;
        data = new int[cap];
        for(unsigned i = 0; i < sz; i++){
            data[i] = expand[i];
        }
        delete[] expand;
}

void IntVector::expand(unsigned amount){
    int* expand = data;
    cap += amount;
    data = new int[cap];
    for(unsigned i = 0; i < sz; i++){
        data[i] = expand[i];
    }
    delete[] expand;
}