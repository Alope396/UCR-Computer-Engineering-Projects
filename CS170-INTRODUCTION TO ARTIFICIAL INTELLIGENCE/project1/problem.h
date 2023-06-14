#ifndef __PROBLEM_H__
#define __PROBLEM_H__

#include <string>
#include <vector>
#include <queue>
#include <set>

using namespace std;

class Problem {
    private:
        //using vector so we don't have to deal with pointers and freeing pointers for each node
        vector<vector<Tile>> initial_state;
        vector<vector<Tile>> goal_state;
        Node root;
        Node goal;
        SEARCH_METHODS search_method;

        unsigned int count_expanded_nodes;
        unsigned int maximum_nodes_frontier;

        // operators - move b
        pair<bool, Node> move_b_left(Node nod) const;
        pair<bool, Node> move_b_right(Node nod) const;
        pair<bool, Node> move_b_up(Node nod) const;
        pair<bool, Node> move_b_down(Node nod) const;

        //helper function
        pair<int, int> find_b(vector<vector<char>> state) const; //return i, j
        pair<int, int> find_b_in_tiles(vector<vector<Tile>> state) const; //return i, j
        vector<Node> expand(Node initial, Node state) const;

        void print_success(int depth);
        void print_failure();

    public:
        Problem();
        Problem(vector<vector<Tile>> initial_state, int num_rows, int num_cols, SEARCH_METHODS search_method);

        //initial state
        vector<vector<Tile>> get_initial_state() const;
        void set_initial_state(vector<vector<Tile>> initial_state); //probbaly won't use
        
        //search for solution
        bool search();
        Node get_goal() const;

};

#endif 