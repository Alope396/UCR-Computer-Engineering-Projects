#ifndef __NODE_H__
#define __NODE_H__

#include <string>
#include <vector>
#include <set>
#include "validator.h"

using namespace std;

enum SEARCH_METHODS {
    NONE = -1,
    FORWARD_SELECTION,
    BACKWARD_ELIMINATION,
    SPECIAL_ALGORITHM
};

class Node {
    private: 
        set<int> state; //features subset
        vector<Node> children;
        int depthLevel;
        double accuracy;
        SEARCH_METHODS searchMethod;

    public:
        Node();
        Node(set<int> state, SEARCH_METHODS searchMethod, int depthLevel);

        void printState() const;
        int getDepthLevel() const;
        double getAccuracy() const;
        set<int> getState() const;
        SEARCH_METHODS getSearchMethod() const;

        void printExpand();
        double evaluation(Validator validator); //k-fold cross validation (accuracy)
        
        //compare state (data)
        bool operator==(const Node& rhs) const; 
        bool operator<(const Node& rhs) const;
        bool operator>(const Node& rhs) const;
  
};

#endif