#include "WordLadder.h"
#include <fstream>
#include <iostream>
#include <list>
#include <stack>
#include <queue>

using namespace std;

WordLadder::WordLadder(const string &filename){
    ifstream inFS;
    string words;

    inFS.open(filename);
    if(!inFS.is_open()){
        cout<< "Error opening file" << endl;
        return ;
    }
    while(getline(inFS, words)){
        if(words.size() != 5){
            cout<< "Invalid word size" << endl;
            return ;
        }
        dict.push_back(words);
    }
    inFS.close();
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile){
    ofstream oFS;
    oFS.open(outputFile);
    stack<string> Stack;
    queue<stack<string>> Queue;
    string word;
    string nextWord;

    list<string>::iterator it = dict.begin();
    Stack.push(start);
    dict.remove(start);
    Queue.push(Stack);
    if(start == end){
        oFS<< start;
        return;
    }
    while(!Queue.empty()){
        word = Queue.front().top();
        for(it = dict.begin(); it != dict.end(); it++){
            unsigned int counter = 0;
            // cout<< counter << endl;
            nextWord = *it;
            // cout<< word << endl;
            for(unsigned int j = 0; j < 5; j++){
                if(word.at(j) != nextWord.at(j)){
                    counter++;
                }
            }
            // cout<< counter;
            if(counter == 1){
                if(nextWord == end){
                    // cout<< "Adding " << nextWord << endl;
                    Queue.front().push(end);
                    stack<string> newStack = Queue.front();
                    int size = 0;
                    vector <string> wordLadder;
                    while(!newStack.empty()){
                        wordLadder.push_back(newStack.top());
                        newStack.pop();
                        size++;
                    }
                    for(unsigned k = size - 1; k > 0; k--){
                        oFS<< wordLadder.at(k);
                        if(k > 0){
                            oFS<< " ";
                        }
                    }
                    oFS<< wordLadder.at(0);
                    oFS.close();
                    return;
                }
                else{
                    stack<string> newStack = Queue.front();
                    // cout<< "Adding " << nextWord << endl;
                    newStack.push(nextWord);
                    Queue.push(newStack);
                    it = dict.erase(it);
                    it--;
                }
            }
            // it = next(dict.begin(), i);
        }
        Queue.pop();
    }
    oFS<< "No Word Ladder Found." << endl;
    oFS.close();
}