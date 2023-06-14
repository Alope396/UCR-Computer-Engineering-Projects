#include <string>

using namespace std;

struct Node{
    string data;
    int height;
    Node* right;
    Node* left;
    Node* prev;
    Node(string data) : data(data), height(0), right(nullptr), left(nullptr), prev(nullptr){}
};