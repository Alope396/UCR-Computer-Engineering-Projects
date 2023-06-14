#include <string>

using namespace std;

struct Node{
    string data;
    int count;
    Node* left;
    Node* right;
    Node* previous;
    Node(string data) : data(data), count(1), left(nullptr), right(nullptr), previous(nullptr){}
};

// class Node{
//     private:
//         string data;
//         int count;
//         Node* left;
//         Node* right;
    
//     public:
//         Node();
//         Node(string data);
// };