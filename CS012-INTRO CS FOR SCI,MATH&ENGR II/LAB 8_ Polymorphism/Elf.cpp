#include <string>
#include <iostream>
#include "Elf.h"
using namespace std;

Elf::Elf(const string& name, double health, double attackStrength, const string familyName) : Character(ELF, name, health, attackStrength){
    this->familyName = familyName;
}

string Elf::getFamilyName(){
    return familyName;
}

double Elf::damageDone(){
    return (attackStrength * (health / MAX_HEALTH));
}

void Elf::attack(Character & target){
    if(target.getType() == ELF){
            Elf &opp = dynamic_cast<Elf &>(target);
            if(opp.getFamilyName() != this->getFamilyName()){
                opp.damage(this->damageDone());
                cout<< "Elf " << this->getName() << " shoots an arrow at " << opp.getName() << " --- TWANG!!" << endl;
                cout<< target.getName() << " takes " << this->damageDone() << " damage." << endl;
            }
            else{
                cout<< "Elf " << this->getName() << " does not attack Elf " << target.getName() << "." << endl;
                cout<< "They are both members of the " << this->getFamilyName() << " family." << endl;
            }
    }
    else
    {
        target.damage(this->damageDone());
        cout<< "Elf " << this->getName() << " shoots an arrow at " << target.getName() << " --- TWANG!!" << endl;
        cout<< target.getName() << " takes " << this->damageDone() << " damage." << endl;
    }
}