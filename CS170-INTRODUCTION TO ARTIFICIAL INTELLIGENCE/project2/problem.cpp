#include <algorithm>
#include <iostream>
#include "problem.h"

using namespace std;

Problem::Problem() {
  
}

Problem::Problem(int numFeatures, SEARCH_METHODS searchMethod, Validator validator) {
    switch(searchMethod) {
        case FORWARD_SELECTION:
            //start with empty set of features and then add features

            //end with full set of features
            for (int i = 1; i <= numFeatures; i++) {
                goalState.insert(i);
            }

            break;

        case BACKWARD_ELIMINATION:
            //start with full set of features and then remove features
            for (int i = 1; i <= numFeatures; i++) {
                initialState.insert(i);
            } 

            //end with empty set of features

            break;

        case SPECIAL_ALGORITHM:

            break;

        default:
            break;
            
    }   
    
    this->validator = validator;

    rootNode = Node(initialState, searchMethod, 0);
    //cout << "rootNode: ";
    //rootNode.printState();
    cout << endl;

    goalNode = Node(goalState, searchMethod, 0);
    //cout << "goalNode: ";
    //goalNode.printState();
    cout << endl;

    this->numFeatures = numFeatures;
    this->searchMethod = searchMethod;
    //cout << "searchMethod=" << this->searchMethod << endl;
    //cout <<endl;
}

pair<bool, Node> Problem::addFeature(Node node, int feature) {
    //add feature
    set<int> state = node.getState();
    state.insert(feature);

    if (state.size() == node.getState().size()) {
        return {false, node};
    }

    //create new node with the added feature
    Node newNode = Node(state, searchMethod, node.getDepthLevel()+1);

    return {true, newNode};
}

pair<bool, Node> Problem::removeFeature(Node node, int feature) {
    //remove feature
    set<int> state = node.getState();
    
    state.erase(feature); //erase feature

    /*cout << "{";
    for (set<int>::iterator it = state.begin(); it != state.end(); it++) {
        cout << *it << " ";
    }
    cout << "}" << endl;
    */

    if (state.size() == node.getState().size()) {
        return {false, node};
        //cout << "removeFeature: false" << endl; 
    }

    //create new node with the added feature
    Node newNode = Node(state, searchMethod, node.getDepthLevel()+1);

    //cout << "removeFeature: true" << endl; 
    return {true, newNode};
}

/*bool Problem::isFeatureInState(vector<int> state, int feature) const {
    //find feature number in state
    auto it = find(state.begin(), state.end(), feature);

    //if it == end, did not find feature number in state vector
    if (it == state.end()) {
        return false;
    }
    
    return true;
}
*/


Node Problem::expand(Node node) {
    //expanded nodes
    vector<Node> nodes;

    //set<int> state = node.getState();

    pair<bool, Node> addNode;

    switch(searchMethod) {
        case FORWARD_SELECTION:
            for (int i = 1; i <= numFeatures; i++) {
                addNode = addFeature(node, i);
                if (addNode.first) {
                    nodes.push_back(addNode.second);
                }
            }

            break;

        case BACKWARD_ELIMINATION:
            for (int i = 1; i <= numFeatures; i++) {
                addNode = removeFeature(node, i);
                if (addNode.first) {
                    nodes.push_back(addNode.second);
                }
            }

            break;

        case SPECIAL_ALGORITHM:

            break;

        default:

            break;
    }

    //get evaulation for all of the nodes
    for (int i = 0; i < nodes.size(); i++) {
        nodes.at(i).evaluation(this->validator);
        nodes.at(i).printExpand();
    }

    //get the best accuracy between the expanded nodes
    Node maxNode = maxScore(nodes);

    //cout << "expand, print max node:";
    //maxNode.printState();
    //cout << endl;
    //return node for the children to be added to the priority queue (get the maximum score between the nodes expanded)
    return maxNode;

}

//best feature between node of the same depth (same # of features level)
Node Problem::maxScore(vector<Node> nodes) const{
    if (nodes.empty()) {
        cout << "Error: nodes is empty." << endl;
        return Node();
    }
    Node maxNode = nodes.at(0); //get node with highest accuracy 

    for (int i = 0; i < nodes.size(); i++) {
        if (nodes.at(i).getAccuracy() > maxNode.getAccuracy()) {
            maxNode = nodes.at(i);
        }
    }

    printf("\nFeature subset ");
    maxNode.printState();
    // cout << "was best, accuracy is " << maxNode.getAccuracy() << "%" << endl;
    printf("was best, accuracy is %.2f %\n\n", (maxNode.getAccuracy()*100));

    return maxNode;
}

//get the best feature combination
bool Problem::search() {
    if (rootNode == goalNode) {
        // output goal msg, return initial state
        //printSuccess(rootNode);   
        return true;
    }

    // Initialize with std::greater to use min heap PQ
    priority_queue<Node, vector<Node>, std::greater<Node>> frontier;

    if (frontier.empty()) {
        printf("Initial state: ");

        rootNode.evaluation(this->validator);
        rootNode.printExpand();
        frontier.push(rootNode);

        printf("\n");
    }

    while(!frontier.empty()) {
        //pop node from frontier
        Node currNode = frontier.top();
        frontier.pop();

        path.push_back(currNode);

        //check if node is goal node
        if(currNode == goalNode) {
            // output goal msg
            //printSuccess(currNode);
            return true;
        }

        // else add children to frontier
        Node child = expand(currNode);
        if (child.getSearchMethod() == NONE) {
            cout << "Error: search method failed";
            return false;
        }

        frontier.push(child);

        //cout << "frontier size: " << frontier.size() << endl;

    }
    // return failure if frontier is empty, print failure msg
    printFailure();


    return false;
}

//use path vector to get the best feature combination (highest accuracy)
Node Problem::bestFeatureSet() const {
    Node maxNode = path.at(0); //get node with highest accuracy 

    for (int i = 0; i < path.size(); i++) {
        //printf("path.at(%d).getAccuracy(): %f\n", i, path.at(i).getAccuracy());
        //printf("path.at(%d).printState(): ", i);
        //path.at(i).printState();
        //cout << endl;
        
        if (path.at(i).getAccuracy() > maxNode.getAccuracy()) {
            maxNode = path.at(i);
        }
    }

    return maxNode;
}

void Problem::printBestFeatureSet(Node node) {
    cout << "Finished search!! The best feature subset is ";
    node.printState();
    printf(", which has an accuracy of %.2f", (node.getAccuracy() * 100));
}

void Problem::printSuccess(Node node) {
    cout << "Goal reached!! ";
    node.printState();
    cout << endl;
}

void Problem::printFailure() {
    cout << "Unfortunately, no solution is possible for this problem. :(" << endl;
   
}