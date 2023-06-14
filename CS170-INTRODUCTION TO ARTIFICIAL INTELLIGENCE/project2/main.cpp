#include <iostream>
#include "problem.h"
#include "validator.h"
#include <iomanip>
#include <fstream>
using namespace std;

float defaultRate(int commonClassSize, int datasetSize) {
    //size of common class / dataset
    float accuracy = (float) commonClassSize / (float) datasetSize;

    //temporary
    float accuracy_rand = (float) (rand() % 100) + ( ((float) rand() ) / (float) RAND_MAX);

    return accuracy_rand;
}

int main() {
    //get user's input
    int searchMethodInput;

    cout << "Welcome to Ryan Le (rle026), Aidan Lopez (alope396), Brandon Tran (btran117), and Vy Vo (vvo025) Project 2." << endl;
    
    cout << "Select feature algorithm: \n1. Forward Selection \n2. Backward Elimination \n3. Special Algorithm" << endl;
    cin >> searchMethodInput;
    
    SEARCH_METHODS searchMethod;
    switch(searchMethodInput) {
        case 1:
            searchMethod = FORWARD_SELECTION;
            break;

        case 2:
            searchMethod = BACKWARD_ELIMINATION;
            break;

        case 3:
            searchMethod = SPECIAL_ALGORITHM;
            break;

        default:
            searchMethod = NONE;
            cout << "Select a valid search method!" << endl;
            return 0;
            break;
    }

    cout << "search method = " << searchMethod+1 << endl;
    cout << "Please enter the file path for your data: " << endl;
    string inputFile;
    cin>> inputFile;
    ifstream testData;
    testData.open(inputFile);
    if(!testData.is_open()){
        cout << "Invalid file path. Exiting program." << endl;
        return 0;
    }
    testData.close();


    Validator validator;
    validator.loadDataset(inputFile);

    int numFeatures = validator.getNumFeatures();
    //int numFeatures = 0;

    double defaultRate = validator.defaultRate();

    printf("\nRunning nearest neighbor with no features (default rate), using \"leaving-one-out\" evaluation, we get an accuracy of %.2f %\n\n", defaultRate*100); 

    cout << "Beginning search...";

    // Find number of features total by -> get from validator
    Problem problem(numFeatures, searchMethod, validator);

    bool success = problem.search();
    // cout << "success: " << success << endl;

    // cout << endl;
    if (success) {
        Node bestSubset = problem.bestFeatureSet();
        problem.printBestFeatureSet(bestSubset);
    }

    return 0;
}