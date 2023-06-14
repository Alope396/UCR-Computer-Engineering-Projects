#include <string>
#include "Character.h"
using namespace std;

#ifndef __ELF_H__
#define __ELF_H__

class Elf : public Character{
    private:
        string familyName;
    public:
    Elf(const string&, double, double, const string);
    string getFamilyName();
    double damageDone();
    void attack(Character & target);
};

#endif