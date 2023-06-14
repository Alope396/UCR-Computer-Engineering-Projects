#include <string>
#include <iostream>

#include "Wizard.h"

using namespace std;

Wizard::Wizard(const string& name, double health, double attackStrength, const int rank) : Character(WIZARD, name, health, attackStrength){
    this->rank = rank;
}

int Wizard::getRank(){
    return rank;
}

double Wizard::damageDone(double r){
    if(r == 0){
        return attackStrength;
    }
    else{

        return (attackStrength * (double(rank) / double(r)));
    }
}

void Wizard::attack(Character & target){
    if(target.getType() == WIZARD){
            Wizard &opp = dynamic_cast<Wizard &>(target);
            opp.damage(this->damageDone(opp.getRank()));
            cout<< "Wizard " << this->getName() << " attacks " << target.getName() << " --- POOF!!" << endl;
            cout<< target.getName() << " takes " << this->damageDone(double(opp.getRank())) << " damage." << endl;
    }
    else{
        target.damage(this->damageDone(0));
        cout<< "Wizard " << this->getName() << " attacks " << target.getName() << " --- POOF!!" << endl;
        cout<< target.getName() << " takes " << this->damageDone(0) << " damage." << endl;
    }
}