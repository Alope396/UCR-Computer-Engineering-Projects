#include <string>

#include "Character.h"

using namespace std;

class Wizard : public Character{
    private:
        int rank;
    public:
        Wizard(const string&, double, double, const int);
        int getRank();
        double damageDone(double r);
        void attack(Character & target);
};