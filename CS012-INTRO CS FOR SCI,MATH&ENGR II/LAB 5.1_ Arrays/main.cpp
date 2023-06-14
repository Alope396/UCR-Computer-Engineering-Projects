//include any standard libraries needed
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
//  - Passes in an array along with the size of the array.
//  - Returns the mean of all values stored in the array.
double mean(const double array[], int arraySize);

//  - Passes in an array, the size of the array by reference, and the index of a value to be removed from the array.
//  - Removes the value at this index by shifting all of the values after this value up, keeping the same relative order of all values not removed.
//  - Reduces arraySize by 1.
void remove(double array[], int &arraySize, int index);


// - Passes in an array and the size of the array.
// - Outputs each value in the array separated by a comma and space, with no comma, space or newline at the end.
void display(const double array[], int arraySize);


const int ARR_CAP = 100;

int main(int argc, char *argv[]) {
   string fileName = argv[1];
   fstream inFS;
   double data;
   int i = 0;
   int userInput;

   // verify file name provided on command line
   inFS.open(fileName);
   if(!inFS.is_open())
   {
      cout<< "Error opening file: " << fileName << endl;
      return 1;
   }

   // open file and verify it opened
   double arr[ARR_CAP];

   // Declare an array of doubles of size ARR_CAP.
   while(i < ARR_CAP && inFS >> data)
   {
      arr[i] = data;
      i++;
   }

   // Fill the array with up to ARR_CAP doubles from the file entered at the command line.
   cout<< "Mean: " << mean(arr, i) << endl;

   // Call the mean function passing it this array and output the 
   // value returned.
   cout<< "Enter index of value to be removed (0 to " << i-1 << "): " << endl;
   cin>> userInput;

   // Ask the user for the index (0 to size - 1) of the value they want to remove.
   cout<< "Before removing value: ";
   display(arr, i);
	
   // Call the display function to output the array.
   remove(arr, i, userInput);
   
   // Call the remove function to remove the value at the index
   // provided by the user.
   cout<< "After removing value: ";
   display(arr, i);
   
   // Call the display function again to output the array
   // with the value removed.
   cout<< "Mean: " << mean(arr, i);
   
   // Call the mean function again to get the new mean

   
	return 0;
}

double mean(const double array[], int arraySize)
{
   double mean = 0;
   double sum = 0;
   int counter = 0;
   for(int i = 0; i < arraySize; i++)
   {
      sum = sum + array[i];
      counter++;
   }
   mean = sum/counter;
   return mean;
}

void remove(double array[], int &arraySize, int index)
{
   for(int i = index; i < arraySize-1; i++)
   {
      array[i] = array[i+1];
   }
   arraySize = arraySize - 1;
}

void display(const double array[], int arraySize)
{
   for(int i = 0; i < arraySize - 1; i++)
   {
      cout<< array[i] << ", ";
   }
   cout<< array[arraySize - 1];
}