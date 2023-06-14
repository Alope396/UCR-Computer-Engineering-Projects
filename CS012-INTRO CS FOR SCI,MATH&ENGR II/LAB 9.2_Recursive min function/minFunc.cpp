#include "minFunc.h"
#include <iostream>
using namespace std;
// 5124637

const int * min(const int arr[], int arrSize) {
    const int * minVal = &arr[arrSize - 1];
    if(arrSize <= 1){
        return &arr[0];
    }
    else{
        const int * index = min(arr, arrSize - 1);
        if(*minVal > *index){
            minVal = index;
        }
        return minVal;
    }
}