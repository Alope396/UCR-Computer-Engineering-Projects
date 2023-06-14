#ifndef __PROBLEM_H__
#define __PROBLEM_H__

#include <string>
#include <queue>
#include <set>
#include "node.h"
#include "validator.h"

using namespace std;

class Problem {
    private:
        //using set for features (subset) so we don't have to deal with pointers and freeing pointers for each node
        set<int> initialState;
        set<int> goalState;
    
        int numFeatures;

        Node rootNode;
        Node goalNode;
        
        // Validator used to calculate accuracy and load data
        Validator validator;
    
        // operators - add features
        pair<bool, Node> addFeature(Node node, int feature);
        pair<bool, Node> removeFeature(Node node, int feature);

        //search method
        SEARCH_METHODS searchMethod;

        //path of popped nodes from the queue (from initial state to goal state) - use this to get the best solution
        vector<Node> path;

        //helper functions
        Node maxScore(vector<Node> nodes) const; //best feature between node of the same depth (same # of features level)

        Node expand(Node node);
        void printFailure();

        //bool isFeatureInState(vector<int> state, int feature) const;

    public:
        Problem();
        Problem(int numFeatures, SEARCH_METHODS searchMethod, Validator validator);

        //search for best features (highest accuracy) using greedy algorithm (get the path)
        bool search();
        Node bestFeatureSet() const; //use path vector to get the best feature combination (highest accuracy) & print it out
        void printBestFeatureSet(Node node);
        void printSuccess(Node node);
};

#endif 