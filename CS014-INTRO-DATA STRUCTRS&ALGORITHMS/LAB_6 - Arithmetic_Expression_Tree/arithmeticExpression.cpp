#include <stack>
#include <fstream>
#include <sstream>
#include <ostream>
#include "arithmeticExpression.h"

arithmeticExpression::arithmeticExpression(const string& input){
    this->infixExpression = input;
}

void arithmeticExpression::buildTree(){
    string expression = infix_to_postfix();
    stack<TreeNode*> stack;
    char key = 'a';
    for(unsigned int i = 0; i < expression.size(); i++){
        char data = expression.at(i);
        if(data != '*' && data != '+' && data != '-' && data != '(' && data != ')' && data != ' '){
            stack.push(new TreeNode(data, key));
            key++;
        }
        else if(data == '*' || data == '/' || data == '+' || data == '-' || data == '(' || data == ')'){
            TreeNode* newRightNode = stack.top();
            stack.pop();
            TreeNode* newLeftNode = stack.top();
            stack.pop();
            TreeNode* newNode = new TreeNode(data, key);
            key++;
            newNode->left = newLeftNode;
            newNode->right = newRightNode;
            stack.push(newNode);
        }
    }
    this->root = stack.top();
    stack.pop();
}

void arithmeticExpression::infix(){
    infix(root);
}

void arithmeticExpression::prefix(){
    prefix(root);
}

void arithmeticExpression::postfix(){
    postfix(root);
}

void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
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

int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::infix(TreeNode * node){
    if(node == nullptr){
        return;
    }
    if(node->left == nullptr && node->right == nullptr){
        cout<< node->data;
    }
    else{
        cout<< "(";
        infix(node->left);
        cout<<node->data;
        infix(node->right);
        cout<< ")";
    }
}

void arithmeticExpression::prefix(TreeNode * node){
    if(node == nullptr){
        return;
    }
    cout<< node->data;
    prefix(node->left);
    prefix(node->right);
}

void arithmeticExpression::postfix(TreeNode * node){
    if(node == nullptr){
        return;
    }
    postfix(node->left);
    postfix(node->right);
    cout<< node->data;
}

void arithmeticExpression::visualizeTree(ofstream &, TreeNode *){
    return;
}