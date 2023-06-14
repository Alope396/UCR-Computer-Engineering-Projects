#include <cstdlib>
#include <cmath>
#include <iostream>
#include <string>
#include "node.h"
#include "validator.h"

using namespace std;

Node::Node() {
   depthLevel = -1;
   accuracy = -1;
   searchMethod = NONE;
}

Node::Node(set<int> state, SEARCH_METHODS search_method, int depth_level) {
    this->state = state;
    this->depthLevel = depth_level;
    this->searchMethod = search_method;
}

void Node::printState() const {
    auto it = state.begin();
    if(it == state.end()) { 
        cout << "{";
        cout << "} "; 
        return; 
    }

    cout << "{";
    cout << *it;
    it++;

    for(it; it != state.end(); it++) {
        cout << ", " << *it;
    }

    cout << "} ";

}

int Node::getDepthLevel() const {
    return depthLevel;
}

double Node::getAccuracy() const{
    return accuracy;
}

set<int> Node::getState() const {
    return state;
}

SEARCH_METHODS Node::getSearchMethod() const {
    return searchMethod;
}

double Node::evaluation(Validator validator) {

    double accuracy = validator.accuracy(this->state);

    this->accuracy = accuracy;
    return accuracy;
}

void Node::printExpand() {
    printf("\tUsing feature(s) ");
    printState();
    //cout << "accuracy is " << accuracy << "%" << endl;
    printf("accuracy is %.2f\n", this->accuracy * 100);
}

bool Node::operator==(const Node& rhs) const {
    //compare if the node state are the same
    return state == rhs.state;
}
        
bool Node::operator<(const Node& rhs) const {
    //compare evaluation/accuracy of the node (feature subset)
    return accuracy < rhs.accuracy;
}
        
bool Node::operator>(const Node& rhs) const {
    //compare evaluation/accuracy of the node (feature subset)
    return accuracy > rhs.accuracy;
}