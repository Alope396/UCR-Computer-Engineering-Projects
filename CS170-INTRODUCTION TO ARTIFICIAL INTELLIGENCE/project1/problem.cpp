#include <iostream>
#include "node.h"
#include "problem.h"
#include <algorithm>

using namespace std;

Problem::Problem() {

}

Problem::Problem(vector<vector<Tile>> initial_state, int num_rows, int num_cols, SEARCH_METHODS search_method) 
{
    this->initial_state = initial_state;
    root = Node(initial_state, search_method, 0);

    // generate goal state
    vector<vector<Tile>> goal_state;
    for (unsigned i = 0; i < num_rows; i++) {
        vector<Tile> row;
        for (unsigned j = 0; j < num_cols; j++) {
            char value = '0' + (i * num_cols) + j + 1;
            if (value == '9') {
                value = 'b';
            }

            // Instantiate struct object Tile
            struct Tile tile = {value, {i, j}, {value % num_cols, value / num_cols + 1}};
            row.push_back(tile);
        }

        goal_state.push_back(row);
    }

    this->goal_state = goal_state;
    // TODO: set goal depth
    goal = Node(goal_state, search_method, 0);

    this->search_method = search_method;
    count_expanded_nodes = 0;
    maximum_nodes_frontier = 0;

    //create Tree with root
    //Node* root = new Node(initial_state, 0); //depth of root node is 0
    //tree = new Tree(root);
}

vector<vector<Tile>> Problem::get_initial_state() const 
{
    return this->initial_state;
}

void Problem::set_initial_state(vector<vector<Tile>> initial_state) 
{
    this->initial_state = initial_state;
}

// Returns a pair of indices of the current location of b.
// (-1, -1) means b was not found. (should not happen)
pair<int, int> Problem::find_b(vector<vector<char>> state) const {
    // O(N^2) time sheesh
    for (unsigned int i = 0; i < state.size(); i++) {
        for (unsigned int j = 0; j < state[i].size(); j++) {
            if (state[i][j] == 'b') {
                return std::make_pair(i, j);
            }
        }
    }

    return std::make_pair(-1, -1);
}

// Returns a pair of indices of the current location of b after state
// has been converted to tiles.
// (-1, -1) means b was not found. (should not happen)
pair<int, int> Problem::find_b_in_tiles(vector<vector<Tile>> state) const {
    for (unsigned int i = 0; i < state.size(); i++) {
        for (unsigned int j = 0; j < state[i].size(); j++) {
            if (state[i][j].value == 'b') {
                return std::make_pair(i,j);
            }
        }
    }

    return std::make_pair(-1, -1);
}

// Tree* Problem::build_tree() const {
//     Node* root = tree->get_root();
//     Node* curr_node = root;


//     return tree;
// }

void Problem::print_success(int depth) {
    cout << "Goal!!!" << endl;
    cout << "To solve this problem, the search algorithm expanded a total of " << count_expanded_nodes << " nodes." << endl;
    cout << "The maximum number of nodes in the queue at any one time was " << maximum_nodes_frontier << "." << endl;
    cout << "The depth of the goal node was " + to_string(depth) << "." << endl;    
}

void Problem::print_failure() {
    cout << "Unfortunately, no solution is possible for this problem. :(" << endl;
    cout << "To solve this problem, the search algorithm expanded a total of " << count_expanded_nodes << " nodes." << endl;
    cout << "The maximum number of nodes in the queue at any one time was " << maximum_nodes_frontier << "." << endl;
}

/**
 * @brief 
*/

bool Problem::search() {

    set<vector<vector<Tile>>> visited_states;
    if (root == goal) {
        // output goal msg, return initial state
        print_success(0);
        return true;
    }

    // Initialize with std::greater to use min heap PQ
    priority_queue<Node, vector<Node>, std::greater<Node>> frontier;

    if(visited_states.empty()){
        frontier.push(root);
        visited_states.insert(root.get_data());
    }

    while(!frontier.empty() || frontier.top().get_depth_level() < 10) {
        //pop node from frontier
        Node curr_node = frontier.top();
        frontier.pop();

        //check if node is goal node
        if(curr_node == goal) {
            // output goal msg
            print_success(curr_node.get_depth_level());
            return true;
            
        }

        // else add children to frontier
        vector<Node> children = expand(root, curr_node);
        count_expanded_nodes += 1;
        for(int i = 0; i < children.size(); i++) {
            try {
                if(visited_states.find(children[i].get_data()) == visited_states.end()){ //searches to end of the set. if it doesnt find it it will add to set and frontier.
                    frontier.push(children[i]);
                    visited_states.insert(children[i].get_data());
                }
            }
            catch (int e) {
                printf("exception caught %d\n", e);
            }
        }
        maximum_nodes_frontier = max(maximum_nodes_frontier, (unsigned int)frontier.size());
        frontier.top().print_expand();
    }
    // return failure if frontier is empty, print failure msg
    print_failure();


    return false;
}

Node Problem::get_goal() const {
    return goal;
}

vector<Node> Problem::expand(Node initial, Node state) const {
    vector<Node> outcomes;

    pair<bool, Node> left = move_b_left(state);
    if(left.first) { outcomes.push_back(left.second); }
    //else {printf("can't go left\n"); left.second.print_data(); printf("\n");}
    
    pair<bool, Node> right = move_b_right(state);
    if(right.first) { outcomes.push_back(right.second); }
    //else {printf("can't go right\n"); right.second.print_data(); printf("\n");}

    pair<bool, Node> up = move_b_up(state);
    if(up.first) { outcomes.push_back(up.second); }
    //else{printf("can't go up\n"); up.second.print_data(); printf("\n");}

    pair<bool, Node> down = move_b_down(state);
    if(down.first) { outcomes.push_back(down.second); }
    //else{printf("can't go down\n"); down.second.print_data(); printf("\n");}

    return outcomes;
    //return {leftNode, rightNode, upNode, downNode};
    
}
// Moves tile b once to the left.
pair<bool, Node> Problem::move_b_left(Node nod) const {
    vector<vector<Tile>> state = nod.get_data();

    // Get b's current indices
    std::pair<int, int> curr_b_idx = this->find_b_in_tiles(state);
    //printf("move left curr_b_idx: (%d, %d)\n", curr_b_idx.first, curr_b_idx.second);

    if (curr_b_idx.second == 0) {
        // Can't move since on left side of board
        return std::make_pair(false, nod);
    }
    else {
        // Copy b tile 
        Tile newB = state[curr_b_idx.first][curr_b_idx.second];
        // Change newB's curr idx to reflect moving to left
        newB.curr_idx = std::make_pair(curr_b_idx.first, curr_b_idx.second - 1);

        // Copy tile that is to the left of b
        Tile leftTile = state[curr_b_idx.first][curr_b_idx.second - 1];
        // Change left tile to reflect moving to the right (swapping with b)
        leftTile.curr_idx = std::make_pair(curr_b_idx.first, curr_b_idx.second);

        // Now reassign
        state[curr_b_idx.first][curr_b_idx.second] = leftTile;
        state[curr_b_idx.first][curr_b_idx.second - 1] = newB;
        /*
        printf("move left state:\n");
        nod.print_data();
        printf("move left curr_b_idx: (%d, %d)\n", curr_b_idx.first, curr_b_idx.second);
        printf("move left newB: (%d, %d)\n", newB.curr_idx.first, newB.curr_idx.second);
        printf("move left leftTile: (%d, %d)\n", leftTile.curr_idx.first, leftTile.curr_idx.second);
        */
        Node output = Node(state, search_method, nod.get_depth_level() + 1);
        return std::make_pair(true, output);
    }
}

// Moves tile b once to the right.
pair<bool, Node> Problem::move_b_right(Node nod) const {
    vector<vector<Tile>> state = nod.get_data();

    // Get b's current indices 
    std::pair<int, int> curr_b_idx = this->find_b_in_tiles(state);
    //printf("move right curr_b_idx: (%d, %d)\n", curr_b_idx.first, curr_b_idx.second);

    if (curr_b_idx.second == 2) {
        // Can't move since on right side of board
        return std::make_pair(false, nod);
    }
    else {
        // Copy b tile 
        Tile newB = state[curr_b_idx.first][curr_b_idx.second];
        // Change newB's curr idx to reflect moving to right
        newB.curr_idx = std::make_pair(curr_b_idx.first, curr_b_idx.second + 1);

        // Copy tile that is to the right of b
        Tile rightTile = state[curr_b_idx.first][curr_b_idx.second + 1];
        // Change right tile to reflect moving to the left (swapping with b)
        rightTile.curr_idx = std::make_pair(curr_b_idx.first, curr_b_idx.second);

        // Now reassign
        state[curr_b_idx.first][curr_b_idx.second] = rightTile;
        state[curr_b_idx.first][curr_b_idx.second + 1] = newB;
        /*
        printf("move right state:\n");
        nod.print_data();
        printf("move right curr_b_idx: (%d, %d)\n", curr_b_idx.first, curr_b_idx.second);
        printf("move right newB: (%d, %d)\n", newB.curr_idx.first, newB.curr_idx.second);
        printf("move right rightTile: (%d, %d)\n", rightTile.curr_idx.first, rightTile.curr_idx.second);
        */
        Node output = Node(state, search_method, nod.get_depth_level() + 1);
        return std::make_pair(true, output);
    }
}

// Moves tile b once upwards.
pair<bool, Node> Problem::move_b_up(Node nod) const {
    vector<vector<Tile>> state = nod.get_data();
    // Get b's current indices
    std::pair<int, int> curr_b_idx = this->find_b_in_tiles(state);
    //printf("move up curr_b_idx: (%d, %d)\n", curr_b_idx.first, curr_b_idx.second);

    if (curr_b_idx.first == 0) {
        // Can't move since on top side of board
        return std::make_pair(false, nod);
    }
    else {
        // Copy b tile 
        Tile newB = state[curr_b_idx.first][curr_b_idx.second];
        // Change newB's curr idx to reflect moving up
        newB.curr_idx = std::make_pair(curr_b_idx.first - 1, curr_b_idx.second);

        // Copy tile that is above b
        Tile aboveTile = state[curr_b_idx.first - 1][curr_b_idx.second];
        // Change above tile to reflect moving down (swapping with b)
        aboveTile.curr_idx = std::make_pair(curr_b_idx.first - 1, curr_b_idx.second);

        // Now reassign
        state[curr_b_idx.first][curr_b_idx.second] = aboveTile;
        state[curr_b_idx.first - 1][curr_b_idx.second] = newB;
        /*
        printf("move up state:\n");
        nod.print_data();
        printf("move up curr_b_idx: (%d, %d)\n", curr_b_idx.first, curr_b_idx.second);
        printf("move up newB: (%d, %d)\n", newB.curr_idx.first, newB.curr_idx.second);
        printf("move up aboveTile: (%d, %d)\n", aboveTile.curr_idx.first, aboveTile.curr_idx.second);
        */
        Node output = Node(state, search_method, nod.get_depth_level() + 1);
        return std::make_pair(true, output);
    }
}

// Moves tile b once downwards.
pair<bool, Node> Problem::move_b_down(Node nod) const {
    vector<vector<Tile>> state = nod.get_data();
    // Get b's current indices
    std::pair<int, int> curr_b_idx = this->find_b_in_tiles(state);
    //printf("move down curr_b_idx: (%d, %d)\n", curr_b_idx.first, curr_b_idx.second);

    if (curr_b_idx.first == 2) {
        // Can't move since on bottom side of board
        return std::make_pair(false, nod);
    }
    else {
        // Copy b tile 
        Tile newB = state[curr_b_idx.first][curr_b_idx.second];
        // Change newB's curr idx to reflect moving down
        newB.curr_idx = std::make_pair(curr_b_idx.first + 1, curr_b_idx.second);

        // Copy tile that is below b
        Tile belowTile = state[curr_b_idx.first + 1][curr_b_idx.second];
        // Change below tile to reflect moving up (swapping with b)
        belowTile.curr_idx = std::make_pair(curr_b_idx.first, curr_b_idx.second);

        // Now reassign
        state[curr_b_idx.first][curr_b_idx.second] = belowTile;
        state[curr_b_idx.first + 1][curr_b_idx.second] = newB;
        /*
        printf("move down state:\n");
        nod.print_data();
        printf("move down curr_b_idx: (%d, %d)\n", curr_b_idx.first, curr_b_idx.second);
        printf("move down newB: (%d, %d)\n", newB.curr_idx.first, newB.curr_idx.second);
        printf("move down belowTile: (%d, %d)\n", belowTile.curr_idx.first, belowTile.curr_idx.second);
        */
        Node output = Node(state, search_method, nod.get_depth_level() + 1);
        return std::make_pair(true, output);
    }
}