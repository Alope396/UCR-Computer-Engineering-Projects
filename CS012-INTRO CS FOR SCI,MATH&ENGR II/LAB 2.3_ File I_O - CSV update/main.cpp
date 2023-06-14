#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
   
   string inputFile;
   string outputFile;
   
   // Assign to inputFile value of 2nd command line argument
   inputFile = argv[1];
   // Assign to outputFile value of 3rd command line argument
   outputFile = argv[2];
   // Create input stream and open input csv file.
   ifstream inFS;
   inFS.open(inputFile);
   // Verify file opened correctly.
   // Output error message and return 1 if file stream did not open correctly.
      if(!inFS.is_open())
      {
         cout<< "Error opening " << inputFile << endl;
         return 1;
      }
   // Read in integers from input file to vector.
      vector<int> inputInt;
      int data;
      while(inFS >> data)
      {
         char wrong;
         inFS >> wrong;
         inputInt.push_back(data);
      }
   // Close input stream.
   inFS.close();
   // Get integer average of all values read in.
   int sum = 0;
   int avg = 0;
   for(unsigned i = 0; i < inputInt.size(); i++)
   {
      sum = sum + inputInt.at(i);
   }
   avg = sum / inputInt.size();
   // Convert each value within vector to be the difference between the original value and the average.
   for(unsigned i = 0; i < inputInt.size(); i++)
   {
      inputInt.at(i) = inputInt.at(i) - avg;
      cout<< inputInt.at(i) << " ";
   }
   // Create output stream and open/create output csv file.
   ofstream outFS;
   outFS.open(outputFile);
   // Verify file opened or was created correctly.
   // Output error message and return 1 if file stream did not open correctly.
   if(!outFS.is_open())
   {
      cout<< "Error opening " << outputFile << endl;
      return 1;
   }
   // Write converted values into ouptut csv file, each integer separated by a comma.
   for(unsigned i = 0; i < inputInt.size(); i++)
   {
      outFS << inputInt.at(i);
      if(i != (inputInt.size())-1)
      {
         outFS << ", ";
      }
   }
   // Close output stream.
   outFS.close();

   return 0;
}