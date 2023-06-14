#include "Node.h"
#include <string>

using namespace std;

class AVLTree{
    private:
    Node* root;
    Node* findUnbalancedNode(Node* );
    void updateHeight(Node* );
    int height(Node* );
    void rotate(Node* );
    void rotateLeft(Node* );
    void rotateRight(Node* );
    void replaceChild(Node* , Node* , Node* );
    void setChild(Node* , string , Node* );
    void printBalanceFactors_R(Node* );
    void visualizeTree(ofstream & outFS, Node* n);

    public:
    AVLTree();
    void insert(const string & );
    void insert_R(Node* , const string & );
    int balanceFactor(Node* );
    void printBalanceFactors();
    void visualizeTree(const string & );
};