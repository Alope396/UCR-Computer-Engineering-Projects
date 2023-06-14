#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "node.h"
#include "problem.h"

using namespace std;

//helper function to find if the element is already in the vector
bool find_element(vector<char> v, char key) {
    if (find(v.begin(), v.end(), key) != v.end()) {
        return true;
    }

    return false;
}

//get target index for input #
// just gonna hardcode this cause my brain is too ded
pair<int, int> get_target_index(char input_value) {
    int i = -1;
    int j = -1;

    switch(input_value) {
        case '1':
            i = 0;
            j = 0;
            break;

        case '2':
            i = 0;
            j = 1;
            break;

        case '3':
            i = 0;
            j = 2;
            break;

        case '4':
            i = 1;
            j = 0;
            break;

        case '5':
            i = 1;
            j = 1;
            break;

        case '6':
            i = 1; 
            j = 2;
            break;

        case '7':
            i = 2;
            j = 0;
            break;

        case '8':
            i = 2;
            j = 1;
            break;

        case '0': 
        case 'b':
            i = 2;
            j = 2;
            break;
        
        default:
            i = -1;
            j = -1;
            break;
    }

    return {i, j};
    
}

//print puzzle
void print_puzzle(vector<vector<Tile>> puzzle) {
    for (unsigned i = 0; i < 3; i++) {
        for (unsigned j = 0; j < 3; j++) {
            cout << puzzle.at(i).at(j).value << " ";
        }

        cout << endl;
    }
}

//convert 2d char vector to 2d Tile vector
vector<vector<Tile>> convert_char_vector_to_Tile_vector(vector<vector<char>> char_puzzle) {
    vector<vector<Tile>> puzzle;

    for (unsigned i = 0; i < 3; i++) {

        vector<Tile> row;
        for (unsigned j = 0; j < 3; j++) {
            if (char_puzzle.at(i).at(j) == '0') { //set '0' to 'b'
                char_puzzle.at(i).at(j) = 'b';
            }

            char value = char_puzzle.at(i).at(j);

            struct Tile tile = {value, {i, j}, get_target_index(value)};
            row.push_back(tile);
            //cout << "value=" << tile.value << "; curr_idx=(" << tile.curr_idx.first << ", " << tile.curr_idx.second << "); target_idx=(" << tile.target_idx.first << ", " << tile.target_idx.second << ")" <<endl;

        }

        puzzle.push_back(row);

    }

    return puzzle;
}

//write interface
int main() {

    //create initial state vector<vector<Tile>> initial_state
    vector<vector<Tile>> initial_state;
    
    //get user input 
    char puzzle_input;
    cout << "Welcome to Ryan Le (862169037), Aidan Lopez (student id), Brandon Tran (student id), Vy Vo (862140774)'s 8 puzzle solver. \nSelect your puzzle: \n1. Default Puzzle \n2. Create Your Own Puzzle" << endl;
    cin >> puzzle_input;

    //check for any invalid inputs for selecting puzzle type, request to enter inputs again
    while (puzzle_input != '1' && puzzle_input != '2') {
        cout << "\nSelect your puzzle: \n1. Default Puzzle \n2. Create Your Own Puzzle" << endl;
        cin >> puzzle_input;
    }

    //create puzzle
    vector<char> row1;
    vector<char> row2;
    vector<char> row3;
    vector<vector<char>> puzzle;

    if (puzzle_input == '1') 
    {
        //create default puzzle

        row1.push_back('1');
        row1.push_back('b');
        row1.push_back('3');

        row2.push_back('4');
        row2.push_back('2');
        row2.push_back('6');

        row3.push_back('7');
        row3.push_back('5');
        row3.push_back('8');

        //set up puzzle
        puzzle.push_back(row1);
        puzzle.push_back(row2);
        puzzle.push_back(row3);

        //convert char vec to Tile vec
        initial_state = convert_char_vector_to_Tile_vector(puzzle);

        //print default puzzle
        cout << "Default Puzzle: " << endl;
        print_puzzle(initial_state);
        cout << endl;
        
    }
    else if (puzzle_input == '2') 
    {
        //create user puzzle
        int num1, num2, num3;
        cout << "Enter your puzzle, use a zero (0) to represent the blank. Please enter numbers 0-8! No repeating numbers!" << endl;
        
        //row 1
        cout << "Enter the first row, use space or tabs between the numbers. Please enter numbers 0-8! No repeating numbers!" << endl;
        cin >> num1 >> num2 >> num3;

        //check for invalid inputs for row1, request for valid inputs
        while(num1 < 0 || num1 > 8 ||
            num2 < 0 || num2 > 8 ||
            num3 < 0 || num3 > 8 || 
            num1 == num2 || num1 == num3 || num2 == num3) 
        {
            cout << "Please enter a valid first row, use space or tabs between the numbers. Please enter numbers 0-8! No repeating numbers!" << endl;
            cin >> num1 >> num2 >> num3;
        }

        //row 1 inputs are valid, add to puzzle as char
        row1.push_back(num1 + '0');
        row1.push_back(num2 + '0');
        row1.push_back(num3 + '0');

        //row 2
        cout << "Enter the second row, use space or tabs between the numbers. Please enter numbers 0-8! No repeating numbers!" << endl;
        cin >> num1 >> num2 >> num3;

        //check for invalid inputs for row1, request for valid inputs
        while(num1 < 0 || num1 > 8 ||
            num2 < 0 || num2 > 8 ||
            num3 < 0 || num3 > 8 || 
            num1 == num2 || num1 == num3 || num2 == num3 ||
            find_element(row1, num1 + '0') || find_element(row1, num2 + '0') || find_element(row1, num3 + '0') ) 
        {
            cout << "Please enter a valid second row, use space or tabs between the numbers. Please enter numbers 0-8! No repeating numbers!" << endl;
            cin >> num1 >> num2 >> num3;
        }

        //row 2 inputs are valid, add to puzzle as string
        row2.push_back(num1 + '0');
        row2.push_back(num2 + '0');
        row2.push_back(num3 + '0');

        //row 3
        cout << "Enter the third row, use space or tabs between the numbers. Please enter numbers 0-8! No repeating numbers!" << endl;
        cin >> num1 >> num2 >> num3;

        //check for invalid inputs for row1, request for valid inputs
        while(num1 < 0 || num1 > 8 ||
            num2 < 0 || num2 > 8 ||
            num3 < 0 || num3 > 8 || 
            num1 == num2 || num1 == num3 || num2 == num3 ||
            find_element(row1, num1 + '0') || find_element(row1, num2 + '0') || find_element(row1, num3 + '0') ||
            find_element(row2, num1 + '0') || find_element(row2, num2 + '0') || find_element(row2, num3+ '0') )
        {
            cout << "Please enter a valid third row, use space or tabs between the numbers. Please enter numbers 0-8! No repeating numbers!" << endl;
            cin >> num1 >> num2 >> num3;
        }

        //row 3 inputs are valid, add to puzzle as string
        row3.push_back(num1 + '0');
        row3.push_back(num2 + '0');
        row3.push_back(num3 + '0');

        //push rows to overall puzzle
        puzzle.push_back(row1);
        puzzle.push_back(row2);
        puzzle.push_back(row3);

        //convert char vector to Tile vector
        initial_state = convert_char_vector_to_Tile_vector(puzzle);

        //print user puzzle
        cout << "Your puzzle: " << endl;
        print_puzzle(initial_state);
        cout << endl;

    }

    //Ask user for search method

    char search_method_input;
    cout << "Select search method: \n1. Uniform Cost \n2. A* Misplaced Tile Heuristic\n3. A* Euclidean Distance Heuristic" << endl;
    cin >> search_method_input;

    //check for any invalid inputs for selecting puzzle type, request to enter inputs again
    while (search_method_input != '1' && search_method_input != '2' && search_method_input != '3') {
        cout << "Select search method: \n1. Uniform Cost \n2. A* Misplaced Tile Heuristic\n3. A* Euclidean Distance Heuristic" << endl;
        cin >> search_method_input;
    }

    SEARCH_METHODS search_method = UNIFORM_COST;

    switch(search_method_input) {
        case '1':
            search_method = UNIFORM_COST;
            break;

        case '2':
            search_method = A_STAR_MISPLACED_TILE_H;
            break;

        case '3':
            search_method = A_STAR_EUCLIDEAN_DIST_H;
            break;

        default:
            search_method = UNIFORM_COST;
    }

    cout << "Search Method = " << search_method+1 << endl;
    cout << endl;

    //create problem
    Problem problem(initial_state, 3, 3, search_method);

    cout << "Goal State:" << endl;
    problem.get_goal().print_data();

    bool success = problem.search();

    return 0;
}