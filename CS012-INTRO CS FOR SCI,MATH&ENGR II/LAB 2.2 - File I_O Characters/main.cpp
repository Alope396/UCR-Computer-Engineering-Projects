#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

// Place charCnt prototype (declaration) here
int charCnt(string fileName, char ch){
   ifstream inFS;
   inFS.open(fileName);
   int total = 0;
   char fileChar;
   
   if(!inFS.is_open())
   {
      cout<< "Error opening " << fileName << endl;
      return -1;
   }
   while(!inFS.eof())
   {
      inFS.get(fileChar);
      if(!inFS.fail())
      {
         if(fileChar == ch)
         {
            total = total + 1;
         }
      }
   }
   return total;
}


int main() {
   string filename;
   char ch;
   int chCnt = 0;
   
   cout << "Enter the name of the input file: ";
   cin >> filename;
   cout << endl;
   cout << "Enter a character: ";
   cin.ignore(); // ignores newline left in stream after previous input statement
   cin.get(ch);
   cout << endl;

   chCnt = charCnt(filename, ch);  
   if(chCnt == -1)
   {
      return 0;
   } 
   else
   {
      cout << "# of " << ch << "'s: " << chCnt << endl;
   }
   
   return 0;
}

// Place charCnt implementation here
