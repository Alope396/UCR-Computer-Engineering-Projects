#include "Heap.h"
#include <iostream>

using namespace std;

Heap::Heap(){
    numItems = 0;
}

void Heap::enqueue(PrintJob* newJob){
    if(this->numItems == MAX_HEAP_SIZE){
        cout<< "Array is already full." << endl;
        return;
    }
    else if(this->numItems == 0){
        arr[this->numItems] = newJob;
        this->numItems++;
        // cout<< this->numItems << endl;
    }
    else{
        // int i = this->numItems;
        // while(i > 0 && arr[(i-1)/2]->getPriority() < newJob->getPriority()){
        //     arr[i] = arr[(i-1)/2];
        //     i = (i-1)/2;
        //     arr[i] = newJob;
        //     this->numItems++;
        //     cout<< this->numItems << endl;
        // }
        this->numItems++;
        arr[this->numItems - 1] = newJob;
        int index = numItems - 1;
        while(index > 0){
            int parentIndex = (index - 1)/2;
            if(arr[index]->getPriority() <= arr[parentIndex]->getPriority()){
                return;
            }
            else{
                PrintJob* temp = arr[index];
                arr[index] = arr[parentIndex];
                arr[parentIndex] = temp;
                index = parentIndex;
            }
        }
    }
}

void Heap::dequeue(){
    // bool valid = false;
    if(this->numItems == 0){
        cout<< "Array is already empty." << endl;
        return;
    }
    arr[0] = arr[this->numItems - 1];
    // delete arr[numItems - 1];
    this->numItems--;
    // cout<< this->numItems << endl;
    // for(int i = 1; i < this->numItems; i++){
    //     if(arr[0]->getPriority() > arr[i]->getPriority()){
    //         valid = true;
    //     }
    // }
    // if(!valid){
    //     trickleDown(0);
    // }
    trickleDown(0);
}

PrintJob* Heap::highest(){
    return arr[0];
}

void Heap::print(){
    cout<< "Priority: " << arr[0]->getPriority() <<  ", Job Number: " << arr[0]->getJobNumber() << ", Number of Pages: " << arr[0]->getPages() << endl;
}

void Heap::trickleDown(int newRoot){
    int i = 2 * newRoot + 1;
    PrintJob* job = arr[newRoot];
    while(i < numItems){
        int highestPriority = job->getPriority();
        int maxIndex = -1;
        for(int j = 0; j < 2 && j + i < numItems; i++){
            if(arr[j + i]->getPriority() > highestPriority){
                highestPriority = arr[j + i]->getPriority();
                maxIndex = j + i;
            }
        }
        if(highestPriority == job->getPriority()){
            return;
        }
        else{
            PrintJob* temp = arr[newRoot];
            arr[newRoot] = arr[maxIndex];
            arr[maxIndex] = temp;
            newRoot = maxIndex;
            i = 2 * newRoot + 1;
        }
    }
}