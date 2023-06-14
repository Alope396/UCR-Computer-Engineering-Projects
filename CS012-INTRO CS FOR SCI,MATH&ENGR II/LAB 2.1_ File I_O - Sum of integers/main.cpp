#include <fstream>
#include <iostream>
#include <cstdlib> //needed for exit function

using namespace std;

int fileSum(string filename){
   ifstream inFS;
   int sum = 0;
   int fileNum;
   inFS.open(filename);
   if(!inFS.is_open())
   {
      cout<< "Error opening " << filename << endl;
      return 1;
   }
   while(!inFS.eof())
   {
      inFS >> fileNum;
      if(!inFS.fail())
      {
         sum = sum + fileNum;
      }
   }
   inFS.close();

   return sum;
}

int main() {

   ifstream inFS;
   string filename;
   int sum = 0;
   
   cout << "Enter the name of the input file: ";
   cin >> filename;
   cout << endl;
   
   sum = fileSum(filename);
   if(sum == 1)
   {
      return 0;
   }

   cout << "Sum: " << sum << endl;
   
   return 0;
}

// Place fileSum implementation here