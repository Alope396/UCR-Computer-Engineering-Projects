
using namespace std;

#include "Character.h" 

Character::Character(HeroType typ, const string & nam, double h, double strength){
    type = typ;
    name = nam;
    health = h;
    attackStrength = strength;
}

HeroType Character::getType() const{
    return type;
}

const string& Character::getName() const{
    return name;
}

int Character::getHealth() const{
   return static_cast <int> (health);
}

void Character::damage(double d){
    this->health = this->health - d;
}

void Character::setHealth(double h){
    health = h;
}

bool Character::isAlive() const{
    if(getHealth() == 0){
        return false;
    }
    else{
        return true;
    }
}