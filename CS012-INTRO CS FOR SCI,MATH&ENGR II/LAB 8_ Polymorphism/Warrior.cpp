#include <string>
#include <iostream>

#include "Warrior.h"

using namespace std;

Warrior::Warrior(const string& name, double health, double attackStrength, const string allegiance) : Character(WARRIOR, name, health, attackStrength){
    this->allegiance = allegiance;
}

string Warrior::getAllegiance(){
    return allegiance;
}

// void Character::damage(double d){
//     this->setHealth(this->getHealth() - d);
// }

double Warrior::damageDone(){
    double dmg = 0;
    dmg = ((health / MAX_HEALTH) * attackStrength);
    return dmg;
}

void Warrior::attack(Character & target){
    if(target.getType() == WARRIOR){
        Warrior &opp = dynamic_cast<Warrior &>(target);
        if(opp.getAllegiance() != this->getAllegiance()){
            double dmg = this->damageDone();
            opp.damage(dmg);
            cout<< "Warrior " << this->getName() << " attacks " << opp.getName() << " --- SLASH!!" << endl;
            cout<< opp.getName() << " takes " << dmg << " damage." << endl;
        }
        else{
            cout<< "Warrior " << this->getName() << " does not attack Warrior " << target.getName() << "." << endl;
            cout<< "They share an allegiance with " << this->getAllegiance() << "." << endl;
        }
    }
    else{
        double dmg = this->damageDone();
        target.damage(dmg);
        cout<< "Warrior " << this->getName() << " attacks " << target.getName() << " --- SLASH!!" << endl;
        cout<< target.getName() << " takes " << dmg << " damage." << endl;
    }
}