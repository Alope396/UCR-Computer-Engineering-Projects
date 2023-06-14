#include <iostream>
#include <vector>

using namespace std;


struct Tile{
    int id;
    int currPos; //current index
    int goalPos; //goal index
    Tile(int value, int start, int goal){id = value; currPos = start; goalPos = goal;}; 
};

vector<Tile> UCS(vector<Tile> v);
int checkCorrect(vector<Tile> v);
void printPuzzle(vector<Tile> v);

int main(){
    vector<Tile> puzzle;
    vector<int> test_input1 = {2,3,0,1,5,4,7,6,8};

    for(int i = 0; i < test_input1.size(); i++){
        Tile tile = Tile(test_input1.at(i), i, test_input1.at(i)-1);
        if(tile.id == 0){
            tile.goalPos = 8;
        }
        puzzle.push_back(tile); //takes the number and subtracts 1 to find the goal index (number is 2 -> index = 1)
    }

    printPuzzle(puzzle);
    cout<< "f(n) = " << checkCorrect(puzzle) << endl;
    puzzle.clear();

    vector<int> test_input2 = {1,2,3,4,5,6,7,8,0};

    for(int i = 0; i < test_input2.size(); i++){
        Tile tile = Tile(test_input2.at(i), i, test_input2.at(i)-1);
        if(tile.id == 0){
            tile.goalPos = 8;
        }
        puzzle.push_back(tile);
    }

    printPuzzle(puzzle);
    cout<< "f(n) = " << checkCorrect(puzzle) << endl;

    return 0;
}

vector<Tile> UCS(vector<Tile> v){
    int empty_index;
    for(int i = 0; i < v.size(); i++){
        if(v.at(i).id == 0){
            empty_index = i;
        }
    }
    return v;
}

int checkCorrect(vector<Tile> v){
    int incorrect = 0;
    int curr_index;
    int goal_index;
    for(int i = 0; i < v.size(); i++){
        curr_index = v.at(i).currPos;
        goal_index = v.at(i).goalPos;
        if(curr_index != goal_index){
            incorrect++;
        }
    }
    return incorrect;
}

void printPuzzle(vector<Tile> v){
    int j = 0;
    for(int i = 0; i < v.size(); i++){
        j = i+1;
        cout<< v.at(i).id << " ";
        if(j%3 == 0){
            cout<< endl;
        }
    }
}