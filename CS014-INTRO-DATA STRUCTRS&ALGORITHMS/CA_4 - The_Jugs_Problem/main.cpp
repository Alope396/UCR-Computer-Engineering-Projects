#include "Jug.h"
#include <string>
#include <iostream>

using namespace std;

int main(){
   string solution;
   Jug head( 3, 5, 4, 1, 1, 1, 1, 1, 2);         
   if(head.solve(solution) != 1) {
      cout << "Error 3" << endl;
   }
   cout << solution << endl;
};