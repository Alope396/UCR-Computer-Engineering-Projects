#include <iostream>
#include <string>

using namespace std;


void flipString(string &string);

int main() {
   string line;
   cout << "Enter a sentence:" << endl;
   getline(cin, line);
   cout << endl;
   cout << line << endl;
   flipString(line);
   cout << line << endl;

   return 0;
}

void flipString(string &line){
   if(line.size() == 0){
      return;
   }
   else{
      string first = line.substr(0,1);
      cout<< "First is now: " << first << endl;
      string remaining = line.substr(1, line.size() - 1);
      cout<< "Remaining is now: " << remaining << endl;
      flipString(remaining);  
      cout<< "Old Line: " << line << endl;
      line = remaining + first;
      cout<< "New Line: " << line << endl; 
      }
}


