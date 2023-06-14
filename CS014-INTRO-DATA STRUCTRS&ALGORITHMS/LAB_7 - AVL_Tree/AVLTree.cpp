#include "AVLTree.h"
#include <fstream>
#include <iostream>

using namespace std;

AVLTree::AVLTree(){
    this->root = nullptr;
}

void AVLTree::insert(const string & input){
    Node* newNode = new Node(input);
    if(this->root == nullptr){
        this->root = newNode;
    }
    else{
        insert_R(this->root, input);
    }
}

void AVLTree::insert_R(Node* key, const string & input){
    if(key->data == input){
        return;
    }
    else if(key->data > input){
        if(key->left == nullptr){
            Node* newNode = new Node(input);
            key->left = newNode;
            newNode->prev = key;
            Node* temp1 = newNode;
            Node* temp2 = findUnbalancedNode(temp1);
            if(temp2 != nullptr){
                rotate(temp2);
            }
            return;
        }
        insert_R(key->left, input);
    }
    else{
        if(key->right == nullptr){
            Node* newNode = new Node(input);
            key->right = newNode;
            newNode->prev = key;
            Node* temp1 = newNode;
            Node* temp2 = findUnbalancedNode(temp1);
            if(temp2 != nullptr){
                rotate(temp2);
            }
            return;
        }
        insert_R(key->right, input);
    }
}

Node* AVLTree::findUnbalancedNode(Node* key){
    if(key != nullptr){
        int balFac = balanceFactor(key);
        if(balFac == -2 || balFac == 2){
            return key;
        }
        return findUnbalancedNode(key->prev);
    }
    return nullptr;
}

int AVLTree::balanceFactor(Node* key){
    if(key != nullptr){
        int left = -1;
        int right = -1;
        updateHeight(key);
        left = height(key->left);
        right = height(key->right);
        return left - right;
    }
    
    return 0;
}

void AVLTree::updateHeight(Node* key){
    int left = -1;
    int right = -1;
    if(key->right != nullptr){
        right = key->right->height;
    }
    if(key->left != nullptr){
        left = key->left->height;
    }
    if(left > right){
        key->height = left;
    }
    else{
        key->height = right;
    }
}

int AVLTree::height(Node* key){
    if(key != nullptr){
        int left = height(key->left);
        int right = height(key->right);
        if(left > right){
            return left + 1;
        }
        else{
            return right + 1;
        }
    }
    
    return -1;
}

void AVLTree::rotate(Node* key){
    int balFac = balanceFactor(key);
    int balFacLeft = balanceFactor(key->left);
    int balFacRight = balanceFactor(key->right);
    if(balFac == -2){
        if(balFacRight == -1 || balFacLeft == -1){
            rotateLeft(key);
        }
        else if(balFacRight == -2 || balFacLeft == -2){
            rotateRight(key->right);
        }
        else{
            rotateRight(key->right);
            rotateLeft(key);
        }
    }
    else if(balFac == 2){
        if(balFacRight== 1 || balFacLeft == 1){
            rotateRight(key);
        }
        else if(balFacRight == 2 || balFacLeft == 2){
            rotateLeft(key->left);
        }
        else{
            rotateLeft(key->left);
            rotateRight(key);
        }
    }
}

void AVLTree::rotateLeft(Node* key){
    Node* node = key->right->left;
    if(key->prev == nullptr){
        this->root = key->right;
        this->root->prev = nullptr;
    }
    else{
        replaceChild(key->prev, key, key->right);
    }
    setChild(key->right, "left", key);
    setChild(key, "right", node);
}

void AVLTree::rotateRight(Node* key){
    Node* node = key->left->right;
    if(key->prev == nullptr){
        this->root = key->left;
        this->root->prev = nullptr;
    }
    else{
        replaceChild(key->prev, key, key->left);
    }
    setChild(key->left, "right", key);
    setChild(key, "left", node);
}

void AVLTree::replaceChild(Node* prev, Node* currNode, Node* newNode){
    if(prev->left == currNode){
        setChild(prev, "left", newNode);
        return;
    }
    else if(prev->right == currNode){
        setChild(prev, "right", newNode);
        return;
    }
}

void AVLTree::setChild(Node* prev, string child, Node* newNode){
    if(child == "left"){
        prev->left = newNode;
    }
    else{
        prev->right = newNode;
    }
    if(newNode != nullptr){
        newNode->prev = prev;
    }
    updateHeight(prev);
}

void AVLTree::printBalanceFactors(){
    printBalanceFactors_R(this->root);
}

void AVLTree::printBalanceFactors_R(Node* currNode){
    if(currNode == nullptr){
        return;
    }
    else{
        printBalanceFactors_R(currNode->left);
        cout<< currNode->data << "(" << balanceFactor(currNode) << "), ";
        printBalanceFactors_R(currNode->right);
    }
}

void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
        }
    }
}