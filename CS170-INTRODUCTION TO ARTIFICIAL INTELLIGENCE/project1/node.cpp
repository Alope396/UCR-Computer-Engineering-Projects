#include <cstdlib>
#include <cmath>
#include <iostream>
#include <string>
#include "node.h"

using namespace std;

Node::Node() {

}

Node::Node(vector<vector<Tile>> state, SEARCH_METHODS search_method, int depth) {
    this->state = state;
    depth_level = depth;
    this->search_method = search_method;
}

bool Node::operator==(const Node& rhs) const {
    if(state.size() != rhs.state.size()) {
        cout << "Warning: Node dimensions do not match.\n" << endl;
    }

    for(int i = 0; i < state.size(); i++) {
        try {
            if(state[i].size() != rhs.state[i].size()) {
                cout << "Warning: Node dimensions do not match.\n" << endl;
            }

            for(int j = 0; j < state[i].size(); j++) {
                if(state[i][j].value != rhs.state[i][j].value) {
                    return false;
                }
            }
        }
        catch(...) {
            throw "Error comparing node equality, node dimensions may not match";
            return false;
        }
    }

    return true;
}

bool Node::operator<(const Node& rhs) const {
    return (depth_level + get_heuristic()) < (rhs.depth_level + rhs.get_heuristic());
}

bool Node::operator>(const Node& rhs) const {
    return (depth_level + get_heuristic()) > (rhs.depth_level + rhs.get_heuristic());
}

double Node::get_heuristic() const {
    switch(search_method) {
        // Uniform Cost Search does not use a heuristic
        case UNIFORM_COST: {
            return 0.0;
            break;
        }

        // Misplaced Tile counts number of total operations to move each tile to its target index
        case A_STAR_MISPLACED_TILE_H: {
            double totalOperations = 0;
            // print_data();
            for(int i = 0; i < state.size(); i++) {
                for(int j = 0; j < state[i].size(); j++) {
                    // add the number of x and y operations to get each tile to the target index
                    if(state[i][j].target_idx.first != state[i][j].curr_idx.first || state[i][j].target_idx.second != state[i][j].curr_idx.second) {
                        //printf("nonmatch state[%d][%d] = %c, target_idx = (%d, %d), curr_idx = (%d, %d)\n", i, j, state[i][j].value, state[i][j].target_idx.first, state[i][j].target_idx.second, state[i][j].curr_idx.first, state[i][j].curr_idx.second);
                        totalOperations += 1.0;
                    }
                    /*
                    else if (state[i][j].target_idx.first == state[i][j].curr_idx.first && state[i][j].target_idx.second == state[i][j].curr_idx.second) {
                        //printf("matched state[%d][%d] = %c, target_idx = (%d, %d), curr_idx = (%d, %d)\n", i, j, state[i][j].value, state[i][j].target_idx.first, state[i][j].target_idx.second, state[i][j].curr_idx.first, state[i][j].curr_idx.second);
                    }
                    */
                }
            }
            return totalOperations;
            break;
        }

        // Euclidean Distance counts the direct distance from each tile to its target index
        case A_STAR_EUCLIDEAN_DIST_H: {
            double totalDistance = 0.0;
            for(int i = 0; i < state.size(); i++) {
                for(int j = 0; j < state[i].size(); j++) {
                    // add the distance from each tile to the target index
                    totalDistance += sqrt((double) (pow(state[i][j].target_idx.first - state[i][j].curr_idx.first, 2) + pow(state[i][j].target_idx.second - state[i][j].curr_idx.second, 2)));
                }
            }
            return totalDistance;
            break;
        }
    }
    return 0;
}

void Node::print_expand() const {
    printf("The best state to expand with g(n) = %d and h(n) = %f is...\n", depth_level, get_heuristic());

    for (unsigned i = 0; i < state.size(); i++) {
        for (unsigned j = 0; j < state[i].size(); j++) {
            cout << state[i][j].value << " ";
        }
        cout << endl;
    }
    printf("Expanding this node...\n\n");
}

vector<vector<Tile>> Node::get_data() const {
    return state;
}

void Node::print_data() const{
    for (unsigned i = 0; i < state.size(); i++) {
        for (unsigned j = 0; j < state[i].size(); j++) {
            cout << state[i][j].value << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Node::print_data(ostream & os) const{
    for (unsigned i = 0; i < state.size(); i++) {
        for (unsigned j = 0; j < state[i].size(); j++) {
            os << state[i][j].value << " ";
        }
        os << endl;
    }
    os << endl;
}

int Node::get_depth_level() const {
    return depth_level;
}
