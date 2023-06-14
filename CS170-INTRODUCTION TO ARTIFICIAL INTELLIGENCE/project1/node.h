#ifndef __NODE_H__
#define __NODE_H__

#include <string>
#include <vector>
#include <set>

using namespace std;

enum SEARCH_METHODS {
    UNIFORM_COST,
    A_STAR_MISPLACED_TILE_H,
    A_STAR_EUCLIDEAN_DIST_H
};

struct Tile {
    char value; //1-8, b
    pair<int, int> curr_idx; //current index
    pair<int, int> target_idx; //goal index

    bool operator<(const Tile& rhs) const {
        return value < rhs.value;
    }

    bool operator>(const Tile& rhs) const {
        return value < rhs.value;
    }

    bool operator==(const Tile& rhs) {
        return value == rhs.value && curr_idx == rhs.curr_idx && target_idx == rhs.target_idx;
    }
};

class Node {
    private:
        vector<vector<Tile>> state;
        int depth_level;
        SEARCH_METHODS search_method;

    public:
        Node();
        Node(vector<vector<Tile>> state, SEARCH_METHODS search_method, int depth);

        vector<vector<Tile>> get_data() const;
        void print_data() const;
        void print_data(ostream &os) const;
        void print_expand() const;

        int get_depth_level() const;
        
        double get_heuristic() const;

        bool operator==(const Node& rhs) const; //compare state (data)
        bool operator<(const Node& rhs) const;
        bool operator>(const Node& rhs) const;

};
#endif