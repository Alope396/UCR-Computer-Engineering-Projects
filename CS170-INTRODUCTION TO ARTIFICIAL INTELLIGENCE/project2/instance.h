#ifndef __INSTANCE__
#define __INSTANCE__

#include <vector>

using namespace std;

struct Instance {
    int id;
    int classLabel;
    vector<double> features;

    Instance(int id, int classLabel, vector<double> f) : id(id), classLabel(classLabel) {
        for(int i = 0; i < f.size(); i++) {
            features.push_back(f[i]);
        }
    }
};

#endif