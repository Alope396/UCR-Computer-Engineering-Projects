#include "Jug.h"

using namespace std;

Jug::Jug(int Cx,int Cy,int N,int cfX,int cfY,int ceX,int ceY,int cpXY,int cpYX){
    this->Cx = Cx;
    this->Cy = Cy;
    this->N = N;
    this->cfX = cfX;
    this->cfY = cfY;
    this->ceX = ceX;
    this->ceY = ceY;
    this->cpXY = cpXY;
    this->cpYX = cpYX;
}

Jug::~Jug(){
}

void Jug::constructGraph(){
    while(!unchecked.empty()){
        unsigned int curr = unchecked.top();
        unchecked.pop();
        for(unsigned i = 0; i < checked.size(); i++){
            if(curr == checked.at(i)){
                checked.push_back(curr);
                unchecked.push(fillX(curr));
                unchecked.push(fillY(curr));
                unchecked.push(emptyX(curr));
                unchecked.push(emptyY(curr));
                unchecked.push(pXY(curr));
                unchecked.push(pYX(curr));
                break;
            }
        }
    }
}

unsigned int Jug::fillX(unsigned int curr){
    Vertex currV = Vertice.at(curr);
    Vertex newV(this->Cx, currV.amountY);
    if(valid(newV)){
        Vertice.at(curr).nextTo.push_back(pair<int, int>(newV.amountX, newV.amountY));
        Vertice.at(curr).position.push_back(pair<int, string>(findIndex(newV), "fill X")); 
    }
    else{
        Vertice.push_back(newV);
        Vertice.at(curr).nextTo.push_back(pair<int, int>(newV.amountX, newV.amountY));
        Vertice.at(curr).position.push_back(pair<int, string>(findIndex(newV), "fill X"));
        Vertice.at(findIndex(newV)).nextTo.push_back(pair<int, int>(Vertice.at(curr).amountX, Vertice.at(curr).amountY));
    }
    return findIndex(newV);
}

unsigned int Jug::fillY(unsigned int curr){
    Vertex currV = Vertice.at(curr);
    Vertex newV(currV.amountX, this->Cy);
    if(valid(newV)){
        Vertice.at(curr).nextTo.push_back(pair<int, int>(newV.amountX, newV.amountY));
        Vertice.at(curr).position.push_back(pair<int, string>(findIndex(newV), "fill Y")); 
    }
    else{
        Vertice.push_back(newV);
        Vertice.at(curr).nextTo.push_back(pair<int, int>(newV.amountX, newV.amountY));
        Vertice.at(curr).position.push_back(pair<int, string>(findIndex(newV), "fill Y"));
        Vertice.at(findIndex(newV)).nextTo.push_back(pair<int, int>(Vertice.at(curr).amountX, Vertice.at(curr).amountY));
    }
    return findIndex(newV);
}

unsigned int Jug::emptyX(unsigned int curr){
    Vertex currV = Vertice.at(curr);
    Vertex newV(0, currV.amountY);
    if(valid(newV)){
        Vertice.at(curr).nextTo.push_back(pair<int, int>(newV.amountX, newV.amountY));
        Vertice.at(curr).position.push_back(pair<int, string>(findIndex(newV), "empty X")); 
    }
    else{
        Vertice.push_back(newV);
        Vertice.at(curr).nextTo.push_back(pair<int, int>(newV.amountX, newV.amountY));
        Vertice.at(curr).position.push_back(pair<int, string>(findIndex(newV), "empty X"));
    }
    return findIndex(newV);
}

unsigned int Jug::emptyY(unsigned int curr){
    Vertex currV = Vertice.at(curr);
    Vertex newV(currV.amountX, 0);
    if(valid(newV)){
        Vertice.at(curr).nextTo.push_back(pair<int, int>(newV.amountX, newV.amountY));
        Vertice.at(curr).position.push_back(pair<int, string>(findIndex(newV), "empty Y")); 
    }
    else{
        Vertice.push_back(newV);
        Vertice.at(curr).nextTo.push_back(pair<int, int>(newV.amountX, newV.amountY));
        Vertice.at(curr).position.push_back(pair<int, string>(findIndex(newV), "empty Y"));
    }
    return findIndex(newV);
}

unsigned int Jug::pXY(unsigned int curr){
    Vertex currV = Vertice.at(curr);
    int X = Vertice.at(curr).amountX;
    int Y = Vertice.at(curr).amountY;
    while(Y < Cy && X > 0){
        Y++;
        X--;
    }
    Vertex newV(X, Y);
    if(valid(newV)){
        Vertice.at(curr).nextTo.push_back(pair<int, int>(newV.amountX, newV.amountY));
        Vertice.at(curr).position.push_back(pair<int, string>(findIndex(newV), "pour X to Y"));
    }
    else{
        Vertice.push_back(newV);
        Vertice.at(curr).nextTo.push_back(pair<int, int>(newV.amountX, newV.amountY));
        Vertice.at(curr).position.push_back(pair<int, string>(findIndex(newV), "pour X to Y"));
    }
    return findIndex(newV);
}

unsigned int Jug::pYX(unsigned int curr){
    Vertex currV = Vertice.at(curr);
    int X = Vertice.at(curr).amountX;
    int Y = Vertice.at(curr).amountY;
    while(Y > 0 && X < Cx){
        X++;
        Y--;
    }
    Vertex newV(X, Y);
    if(valid(newV)){
        Vertice.at(curr).nextTo.push_back(pair<int, int>(newV.amountX, newV.amountY));
        Vertice.at(curr).position.push_back(pair<int, string>(findIndex(newV), "pour Y to X"));
    }
    else{
        Vertice.push_back(newV);
        Vertice.at(curr).nextTo.push_back(pair<int, int>(newV.amountX, newV.amountY));
        Vertice.at(curr).position.push_back(pair<int, string>(findIndex(newV), "pour Y to X"));
    }
    return findIndex(newV);
}

string Jug::dijkstra(){
    for (unsigned int i = 0; i < Vertice.size(); i++) {
        if (Vertice.at(i).amountY == N) {
            break;
        }
        else if (i == Vertice.size() - 1) {
            return "";
        }
    }
    list<pair<int, int>>::iterator nextto;
    list<pair<int, string>>::iterator pos;
    for (unsigned int i = 0; i < Vertice.size(); i++) {
        nextto = Vertice.at(i).nextTo.begin();
        pos = Vertice.at(i).position.begin();
        while (nextto != Vertice.at(i).nextTo.end()) {
            Vertex temp = Vertice.at(findIndex(Vertex(nextto->first, nextto->second)));
            while (pos != Vertice.at(i).position.end()) {
                int index = findIndex(Vertex(nextto->first, nextto->second));
                if (Vertice.at(index) == Vertice.at(pos->first)) {
                    if (Vertice.at(i).dist + findCost(pos->second) < temp.dist) {
                        Vertice.at(findIndex(temp)).dist = Vertice.at(i).dist + findCost(pos->second);
                        Vertice.at(findIndex(temp)).prev = i;
                    }
                }
                pos++;
            }
            nextto++;
            pos = Vertice.at(i).position.begin();
        }
    }
    Vertex shorterPath(0, this->N);
    int newIndex = findIndex(shorterPath);
    while (Vertice.at(newIndex).prev != -1) {
        list<pair<int, int>>::iterator nextto = Vertice.at(Vertice.at(newIndex).prev).nextTo.begin();
        list<pair<int, string>>::iterator pos = Vertice.at(Vertice.at(newIndex).prev).position.begin();
        while (nextto != Vertice.at(Vertice.at(newIndex).prev).nextTo.end()) {
            Vertex temp(nextto->first, nextto->second);
            int B = findIndex(temp);
            if (B == Vertice.at(newIndex).prev) {
                while (pos != Vertice.at(Vertice.at(newIndex).prev).position.end()) {
                    if (pos->first == newIndex) {
                        Solution.push(pos->second);
                    }
                    pos++;
                }
            }
            nextto++;
        }
        newIndex = Vertice.at(newIndex).prev;
    }
    stringstream ss;
    int finalIndex = findIndex(shorterPath);
    ss << Vertice.at(finalIndex).dist;
    string final = "success " + ss.str();
    return "success " + ss.str();
}

bool Jug::valid(Vertex curr) const{
    for(unsigned int i =0; i < Vertice.size(); i++){
        if(Vertice.at(i).amountX == curr.amountX && Vertice.at(i).amountY == curr.amountY){
            return true;
        }
    }
    return false;
}

int Jug::findIndex(Vertex curr) const{
    for(unsigned int i = 0; i < Vertice.size(); i++){
        if(Vertice.at(i).amountX == curr.amountX){
            return i;
        }
    }
    return -1;
}

int Jug::findCost(const string& curr){
    if(curr == "fill X"){
        return this->cfX;
    }
    if(curr == "fill Y"){
        return this->cfY;
    }
    if(curr == "empty X"){
        return this->ceX;
    }
    if(curr == "empty Y"){
        return this->ceY;
    }
    if(curr == "pour X to Y"){
        return this->cpXY;
    }
    if(curr == "pour Y to X"){
        return this->cpXY;
    }
    return -1;
}

int Jug::solve(string &solution){
    if(Cx < 1 || Cy < 1 || Cy > 1000 || Cx > Cy || N < 0 || N > Cy || cfX < 0 || cfY < 0 || ceX < 0|| ceY < 0 || cpXY < 0 || cpYX < 0){
        solution = "";
        return -1;
    }
    Vertex temp(0,0);
    Vertice.push_back(temp);
    Vertice.at(0).dist = 0;
    Vertice.at(0).prev = -1;
    unchecked.push(0);
    constructGraph();
    string answer = dijkstra();
    if(answer.empty()){
        return 0;
    }
    while(!Solution.empty()){
        solution += (Solution.top()) + '\n';
        Solution.pop();
    }
    solution += answer;
    return 1;
}