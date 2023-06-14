#ifndef __CLASSIFIER_H__
#define __CLASSIFIER_H__

#include <vector>
#include "instance.h"

using namespace std;

class Classifier {
    private:
        vector<Instance> trainedData; 

    public:
        void train(vector<Instance>);
        int test(Instance);
};

#endif