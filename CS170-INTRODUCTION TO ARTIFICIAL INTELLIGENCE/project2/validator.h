#ifndef __VALIDATOR__H__
#define __VALIDATOR__H__

#include <vector>
#include <string>
#include "instance.h"
#include "classifier.h"

using namespace std;

class Validator {
    private:
        vector<Instance> dataset; 
        Classifier classifier; // default classifier (unsure of type)
        int numFeatures;
        int sizeOfMostCommonClass;
        int datasetSize;

    public:
        Validator() {
            dataset = vector<Instance>();
            classifier = Classifier();
            numFeatures = 0;
        }

        void loadDataset(string);
        double accuracy();
        double accuracy(set<int>);
        double getSizeOfMostCommonClass();
        double getDatasetSize();
        double defaultRate();
        int getNumFeatures();
};

#endif