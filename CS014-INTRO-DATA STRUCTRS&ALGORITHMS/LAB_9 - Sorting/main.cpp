#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;

int median(int numbers[], int i, int k);
void fillArrays(int arr1[], int arr2[],int arr3[]);
int genRandInt(int low, int high);
int partition_midpoint(int numbers[], int i, int k);
int partition_medianOfThree(int numbers[], int i, int k);
void Quicksort_midpoint(int numbers[], int i, int k);
void Quicksort_medianOfThree(int numbers[], int i, int k);
void InsertionSort(int numbers[], int numbersSize);
void testQuicksortMidpoint(int numbers[]);
void testQuicksortMedianOfThree(int numbers[]);
void testInsertionSort(int numbers[]);

const int NUMBERS_SIZE = 50000;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds

int main(){
    int arr1[NUMBERS_SIZE];
    int arr2[NUMBERS_SIZE];
    int arr3[NUMBERS_SIZE];
    fillArrays(arr1, arr2, arr3);
    testQuicksortMidpoint(arr1);
    testQuicksortMedianOfThree(arr2);
    testInsertionSort(arr3);
};

int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}

void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
    cout<< "Filling Arrays" << endl;
}

int partition_midpoint(int numbers[], int i, int k){
    int midpoint = i + (k - i)/2;
    int pivot = numbers[midpoint];
    bool finished = false;
    while(finished == false){
        while(numbers[i] < pivot){
            i++;
        }
        while(pivot < numbers[k]){
            k--;
        }
        if(i >= k){
            finished = true;
        }
        else{
            int temp = numbers[i];
            numbers[i] = numbers[k];
            numbers[k] = temp;
            i++;
            k--;
        }
    }
    return k;
}

void Quicksort_midpoint(int numbers[], int i, int k){
    if(i >= k){
        return;
    }
    else{
        int lowEndIndex = partition_midpoint(numbers, i, k);
        Quicksort_midpoint(numbers, i, lowEndIndex);
        Quicksort_midpoint(numbers, lowEndIndex + 1, k);
    }
}

int median(int numbers[], int i, int k){
    int low = numbers[i];
    int mid = numbers[i + (k - i)/2];
    int high = numbers[k];
    int median = 0;
    if((low >= high && low <= mid) || (low <= high && low >= mid)){
        median = i;
    }
    else if((high >= low && high <= mid) || (high <= low && high >= mid)){
        median = k;
    }
    else if((mid >= low && mid <= high) || (mid <= low && mid >= high)){
        median = i + (k - i)/2;
    }
    return median;
}

int partition_medianOfThree(int numbers[], int i, int k){
    int medianOfThree = median(numbers, i , k);
    int pivot = numbers[medianOfThree];
    bool finished = false;
    while(finished == false){
        while(numbers[i] < pivot){
            i++;
        }
        while(pivot < numbers[k]){
            k--;
        }
        if(i >= k){
            finished = true;
        }
        else{
            int temp = numbers[i];
            numbers[i] = numbers[k];
            numbers[k] = temp;
            i++;
            k--;
        }
    }
    return k;
}

void Quicksort_medianOfThree(int numbers[], int i, int k){
    if(i >= k){
        return;
    }
    else{
        int lowEndIndex = partition_midpoint(numbers, i, k);
        Quicksort_midpoint(numbers, i, lowEndIndex);
        Quicksort_midpoint(numbers, lowEndIndex + 1, k);
    }
}

void InsertionSort(int numbers[], int numbersSize){
    for(int i = 1; i < numbersSize; i++){
        int j = i;
        while(j >0 && numbers[j] < numbers[j-1]){
            int temp = numbers[j];
            numbers[j] = numbers[j-1];
            numbers[j-1] = temp;
            j--;
        }
    }
}

void testQuicksortMidpoint(int numbers[]){
    clock_t Start = clock();
    Quicksort_midpoint(numbers, 0, NUMBERS_SIZE);
    clock_t End = clock();
    double elapsedTime = (End - Start)/CLOCKS_PER_MS;
    cout<< "Time for Quicksort(midpoint): " << elapsedTime << " ms" << endl;
}

void testQuicksortMedianOfThree(int numbers[]){
    clock_t Start = clock();
    Quicksort_medianOfThree(numbers, 0, NUMBERS_SIZE);
    clock_t End = clock();
    double elapsedTime = (End - Start)/CLOCKS_PER_MS;
    cout<< "Time for Quicksort(median of three): " << elapsedTime << " ms" <<  endl;
}

void testInsertionSort(int numbers[]){
    clock_t Start = clock();
    InsertionSort(numbers, NUMBERS_SIZE);
    clock_t End = clock();
    double elapsedTime = (End - Start)/CLOCKS_PER_MS;
    cout<< "Time for Insertion Sort: " << elapsedTime << " ms" << endl;
}