#include <string>
#include "Character.h"

using namespace std;

class Warrior : public Character{
    private:
        string allegiance;
    public:
        Warrior(const string& , double, double, const string);
        string getAllegiance();
        double damageDone();
        void attack(Character & target);
};