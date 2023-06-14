#include <iostream>
#include <stdexcept>
using namespace std;

const int MAX_SIZE = 20;
template <typename T>
class stack{
    private:
        T data[MAX_SIZE];
        int size;
    
    public:
        stack();
        void push(T val);
        void pop();
        T top();
        bool empty();
};
template <typename T>

stack<T>::stack(){
    size = 0;
}

template <typename T>

void stack<T>::push(T val){
    if(this->size == MAX_SIZE){
        throw overflow_error("Called push on full stack.");
    }
    this->size++;
    data[this->size - 1] = val;
}

template <typename T>

void stack<T>::pop(){
    if(this->size == 0){
        throw out_of_range("Called pop on empty stack.");
    }
    this->size--;
}

template <typename T>

T stack<T>::top(){
    if(this->size == 0){
        throw underflow_error("Called top on empty stack.");
    }
    return data[this->size - 1];
}

template <typename T>

bool stack<T>::empty(){
    if(this->size == 0){
        return true;
    }
    return false;
}