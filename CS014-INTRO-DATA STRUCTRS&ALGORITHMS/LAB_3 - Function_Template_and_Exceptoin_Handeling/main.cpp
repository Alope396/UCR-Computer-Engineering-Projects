#include <iostream>
#include <vector>
#include <time.h>
#include <stdexcept>

using namespace std;

template <typename T>
unsigned min_index(const vector<T> &vals, unsigned index);

template <typename T>
void selection_sort(vector<T> &vals);

template <typename T>
T getElement(vector<T> vals, int index);

vector<char> createVector();

int main(){
    // Part 1
    // vector<int> v {5,3,2,4,6,1};
    // for(unsigned i = 0; i < v.size(); i++){
    //     cout<< v.at(i) << " ";
    // }
    // cout<< endl;
    // selection_sort(v);
    // for(unsigned i = 0; i < v.size(); i++){
    //     cout<< v.at(i) << " ";
    // }
    // Part 2
    srand(time(0));
    vector<char> vals = createVector();
    char curChar;
    int index;
    int numOfRuns = 10;
    while(--numOfRuns >= 0){
       cout << "Enter a number: " << endl;
       cin >> index;
        try{
            if(index < 0 || unsigned(index) > vals.size() - 1){
                throw out_of_range("Invalid Index (Out of range)");
            }
            curChar = getElement(vals,index);
            cout << "Element located at " << index << ": is " << curChar << endl;
        }
        catch(const out_of_range& excpt){
            cout<< excpt.what() << endl;
            cout<< "out of range exception occured" << endl;
        }
    }

    return 0;
};

template <typename T>
unsigned min_index(const vector<T> &vals, unsigned index){
    T min = vals.at(index);
    unsigned minIndex = index;
    for(unsigned i = index; i < vals.size(); i++){
        if(vals.at(i) < min){
            min = vals.at(i);
            minIndex = i;
        }
    }
    return minIndex;
}

template <typename T>
void selection_sort(vector<T> &vals){
    unsigned minIndex;
    for(unsigned i = 0; i < vals.size(); i++){
        minIndex = min_index(vals, i);
        if(minIndex != i){
            T temp = vals.at(i);
            vals.at(i) = vals.at(minIndex);
            vals.at(minIndex) = temp;
        }
    }
}

template <typename T>
T getElement(vector<T> vals, int index){
    return vals.at(index);
}

vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}