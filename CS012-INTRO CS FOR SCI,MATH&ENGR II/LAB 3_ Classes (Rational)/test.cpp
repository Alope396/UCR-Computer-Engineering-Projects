#include <iostream>
#include <fstream>

using namespace std;

int main() {
    string infile;
    string outfile;

    cout << "Please enter input file: " << endl;
    cin >> infile;
    cout << "Please enter output file" << endl;
    cin >> outfile;

    ifstream inFS;
    inFS.open(infile);

    if (!inFS.is_open()){
      return 1;
    }

    const int ARR_CAP = 1000;
    int array[ARR_CAP];
    int x;
    int counter = 0;

    while (inFS >> x){
      array[counter] = x;
      cout<< array[counter] << " ";
      ++counter;
    }
    cout<< counter << endl;
    inFS.close();

    ofstream ofFS;
    ofFS.open(outfile);

    if (!ofFS.is_open()){
      return 1;
    }

    for (unsigned int i = counter - 1; i >= 0; --i){
      cout<< counter << " ";
      // cout<< array[i] << " ";
      // ofFS << array[i];
    }

    ofFS.close();

    return 0;

}
