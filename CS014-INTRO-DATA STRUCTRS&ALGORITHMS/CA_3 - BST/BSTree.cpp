#include "BSTree.h"
#include <iostream>

using namespace std;

BSTree::BSTree(){
    this->root = nullptr;
}

BSTree::~BSTree(){
    delete this->root;
}

void BSTree::insert(const string &newString){
    if(this->root == nullptr){
        Node *newNode = new Node(newString);
        root = newNode;
    }
    else{
        insert_R(newString, this->root);
    }
}

void BSTree::insert_R(const string &newString, Node* currNode){
    if(currNode->data == newString){
        currNode->count++;
        return;
    }
    else if(newString < currNode->data){
        if(currNode->left == nullptr){
            Node* newNode = new Node(newString);
            currNode->left = newNode;
            newNode->previous = currNode;
            return;
        }
        insert_R(newString, currNode->left);
    }
    else{
        if(currNode->right == nullptr){
            Node* newNode = new Node(newString);
            currNode->right = newNode;
            newNode->previous = currNode;
            return;
        }
        insert_R(newString, currNode->right);
    }
}

void BSTree::remove(const string &key){
    return remove_R(key, this->root);
}

void BSTree::remove_R(const string &key, Node* currNode){
    if(currNode != nullptr){
        if(key == currNode->data){
            Node* previous = currNode->previous;
            if(currNode->right == nullptr && currNode->left == nullptr){
                if(currNode->count > 1){
                    currNode->count--;
                    return;
                }
                if(previous == nullptr){
                    this->root = nullptr;
                    return;
                }
                if(previous->left == currNode){
                    previous->left = nullptr;
                    return;
                }
                if(previous->right == currNode){
                    previous->right = nullptr;
                    return;
                }
            }
            else if(currNode->right != nullptr && currNode->left == nullptr){
                if(currNode->count > 1){
                    currNode->count--;
                    return;
                }
                if(previous == nullptr){
                    this->root = currNode->right;
                    currNode->right->previous = nullptr;
                    return;
                }
                Node* successorNode = currNode->right;
                if(previous->left == currNode){
                    if(successorNode->left != nullptr){
                        Node* tempNode = successorNode;
                        bool check = false;
                        while(successorNode->left != nullptr){
                            successorNode = successorNode->left;
                            if(check == false){
                                if(successorNode->left == nullptr && successorNode->right == nullptr){
                                    check = true;
                                    tempNode = successorNode;
                                }
                            }
                        }
                        previous->left = successorNode;
                        tempNode->left = successorNode->right;
                        successorNode->right->previous = tempNode;
                        successorNode->right = tempNode;
                        tempNode->previous = successorNode;
                        successorNode->previous = previous;
                        return;
                    }
                    else{
                        previous->left = successorNode;
                        successorNode->previous = previous;
                    }
                    return;
                }
                else{
                    Node* tempNode = currNode->right;
                    while(tempNode->left != nullptr){
                        tempNode = tempNode->left;
                    }
                    previous->right = tempNode;
                    tempNode->previous = previous;
                    return;
                }
            } 
            else if(currNode->right == nullptr && currNode->left != nullptr){
                if(currNode->count > 1){
                    currNode->count--;
                    return;
                }
                else if(previous == nullptr){
                    this->root = currNode->left;
                    currNode->left->previous = nullptr;
                    return;
                }
                if(previous->left == currNode){
                    Node* successorNode = currNode->left;
                    previous->left = successorNode;
                    successorNode->previous = previous;
                    return;
                }
                else{
                    Node* successorNode = currNode->right;
                    previous->right = successorNode;
                    successorNode->previous = previous;
                    return;
                }
            }
            else if(currNode->right != nullptr && currNode->left != nullptr){
                if(currNode->count > 1){
                    currNode->count--;
                    return;
                }
                Node* temp = currNode->left;
                while(temp->right != nullptr){
                    temp = temp->right;
                }
                Node* successorNode = temp;
                if(previous == nullptr){
                    currNode->left->previous = successorNode;
                    if(currNode->left != successorNode){
                        successorNode->left = currNode->left;
                    }
                    else{
                        if(successorNode->right != nullptr || successorNode->left != nullptr){
                            temp = currNode;
                            while(temp->left != nullptr){
                                temp = temp->left;
                            }
                            while(temp->right != nullptr){
                                temp = temp->right;
                            }
                            Node* tempP = temp->previous;
                            tempP->right = nullptr;
                            temp->previous = nullptr;
                            temp->left = successorNode->left;
                            temp->previous = successorNode;
                            successorNode->left = temp;
                        }
                    }
                    successorNode->right = currNode->right;
                    this->root = successorNode;
                    successorNode->previous = nullptr;
                    return;
                }
                else{
                    if(previous->left == currNode){
                        previous->left = successorNode;
                    }
                    else if(previous->right == currNode){
                        previous->right = successorNode;
                    }
                    if(successorNode->previous->left == successorNode){
                        successorNode->previous->left = successorNode->left;
                    }
                    else if(successorNode->previous->right == successorNode){
                        successorNode->previous->right = successorNode->right;
                    }
                    successorNode->right = currNode->right;
                    successorNode->left = currNode->left;
                    successorNode->previous = currNode->previous;
                }
            }
            return;
        }
        else if(key < currNode->data){
            remove_R(key, currNode->left);
        }
        else if(key > currNode->data){
            remove_R(key, currNode->right);
        }
    }
    return;
}

bool BSTree::search(const string &key) const{
    return search_R(key, this->root);
}

bool BSTree::search_R(const string &key, Node* node) const{
    Node* currNode = node;
    while(currNode != nullptr){
        if(key == currNode->data){
            return true;
        }
        else if(key < currNode->data){
            currNode = currNode->left;
        }
        else if(key > currNode->data){
            currNode = currNode->right;
        }
    }
    return false;
}

Node* BSTree::search_and_return(const string &key) const{
    return search_and_return_R(key, this->root);
}

Node* BSTree::search_and_return_R(const string &key, Node* node) const{
    Node* currNode = node;
    while(currNode != nullptr){
        if(key == currNode->data){
            return currNode;
        }
        else if(key < currNode->data){
            currNode = currNode->left;
        }
        else if(key > currNode->data){
            currNode = currNode->right;
        }
    }
    return nullptr;
}

string BSTree::largest() const{
    return largest_R(this->root);
}

string BSTree::largest_R(Node* key) const{
    Node* currNode = key;
    if(currNode == nullptr){
        return "";
    }
    else{
        string largest = currNode->data;
        while(currNode != nullptr){
            if(currNode->right == nullptr){
                currNode = nullptr;
            }
            else{
                currNode = currNode->right;
                largest = currNode->data;
            }
        }
        return largest;
    }
}

string BSTree::smallest() const{
    return smallest_R(this->root);
}

string BSTree::smallest_R(Node* key) const{
    Node* currNode = key;
    if(currNode == nullptr){
        return "";
    }
    string smallest = currNode->data;
    while(currNode != nullptr){
        if(currNode->left == nullptr){
            currNode = nullptr;
        }
        else{
            currNode = currNode->left;
            smallest = currNode->data;
        }
    }
    return smallest;
}

int BSTree::height(const string& key) const{
    return height_R(search_and_return(key));
}

int BSTree::height_R(Node* node) const{
    if(node == nullptr){
        return -1;
    }
    else{
        int left = height_R(node->left);
        int right = height_R(node->right);
        if(left > right){
            return 1 + left;
        }
        else{
            return 1 + right;
        }
    }
}

void BSTree::preOrder() const{
    cout<< "Preorder = ";
    preOrder_R(this->root);
    cout<< endl;
}

void BSTree::preOrder_R(Node* node) const{
    if(node == nullptr){
        return;
    }
    cout<< node->data << "(" << node->count << "), ";
    preOrder_R(node->left);
    preOrder_R(node->right);
}

void BSTree::postOrder() const{
    cout<< "Postorder = ";
    postOrder_R(this->root);
    cout<< endl;
}

void BSTree::postOrder_R(Node* node) const{
    if(node == nullptr){
        return;
    }
    postOrder_R(node->left);
    postOrder_R(node->right);
    cout<< node->data << "(" << node->count << "), ";
}

void BSTree::inOrder() const{
    cout<< "Inorder = ";
    inOrder_R(this->root);
    cout<< endl;
}

void BSTree::inOrder_R(Node* node) const{
    if(node == nullptr){
        return;
    }
    if(node->left == nullptr && node->right == nullptr){
        cout<< node->data << "(" << node->count << "), ";
    }
    else{
        inOrder_R(node->left);
        cout<< node->data << "(" << node->count << "), ";
        inOrder_R(node->right);
    }
}

