#include <string>
#include <vector>
#include <climits>
#include <list>
#include <sstream>
#include <stack>

using namespace std;

class Vertex{
    friend class Jug;
    public:
        Vertex(int x, int y) : amountX(x), amountY(y){};

    private:
        int amountX;
        int amountY;
        unsigned int dist = INT_MAX;
        int prev = -1;
        list<pair<int, int>> nextTo;
        list<pair<int, string>> position;

        bool operator==(Vertex& rhs){
            return ((rhs.amountX == this->amountX) && (rhs.amountY == this->amountY));
        }
};

class Jug {
    public:
        Jug(int,int,int,int,int,int,int,int,int);
        ~Jug();

        //solve is used to check input and find the solution if one exists
        //returns -1 if invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string &solution);
    private:
        int Cx;
        int Cy;
        int N;
        int cfX;
        int cfY;
        int ceX;
        int ceY;
        int cpXY;
        int cpYX;
        vector<Vertex> Vertice;
        stack<unsigned int> unchecked;
        vector<unsigned int> checked;
        stack<string> Solution;

        void constructGraph();
        unsigned int fillX(unsigned int);
        unsigned int fillY(unsigned int);
        unsigned int emptyX(unsigned int);
        unsigned int emptyY(unsigned int);
        unsigned int pXY(unsigned int);
        unsigned int pYX(unsigned int);
        string dijkstra();
        bool valid(Vertex) const;
        int findIndex(Vertex) const;
        int findCost(const string&);
};
