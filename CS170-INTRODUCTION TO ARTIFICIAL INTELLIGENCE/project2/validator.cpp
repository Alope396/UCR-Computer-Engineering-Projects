#include <string>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <cmath>
#include <ctime>
#include "validator.h"
#include "instance.h"

using namespace std;

/**
 * Returns number of features in a dataset
 * 
 * @param void
 * @returns int - number of features in dataset
 */
int Validator::getNumFeatures() {
    return this->numFeatures;
}

/**
 * Returns size of most common class in dataset
 * 
 * @param void
 * @returns int - size of most common class in dataset
 */
double Validator::getSizeOfMostCommonClass() {
    return this->sizeOfMostCommonClass;
}

/**
 * Returns size of dataset
 * 
 * @param void
 * @returns int - size of dataset
 */
double Validator::getDatasetSize() {
    return this->datasetSize;
}

/**
 * If number of features is 0, then return common class size / data set size 
 * 
 * @param void
 * @returns double - default rate
 */
double Validator::defaultRate() {
    //printf("sizeOfMostCommonClass: %f\n", this->getSizeOfMostCommonClass());
    //printf("dataset.size(): %f\n", this->getDatasetSize());

    double accuracy = (double) sizeOfMostCommonClass / (double) datasetSize;
    return accuracy;
}

/**
 * Load entire feature dataset from input file
 * 
 * @param path - path to dataset
 * @returns void
*/
void Validator::loadDataset(string path) {
    clock_t beginTime = clock();
    dataset = vector<Instance>();
    ifstream input(path);

    int instanceID = 0;
    string delimiter = " ";
    string line;
    int numFeatures = 0;
    int firstInstance = 1;

    int numTimesClass1 = 0;
    int numTimesClass2 = 0;

    // used to calculate sums of each feature while we don't know the number of features
    // used with the assumption that each instance has the same number of features, fails otherwise
    vector<double> sums;

    // read data in rows, converting each row into an instance
    // stringstream used to eliminate all whitespace between data in dataset
    // reference: https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/#
    while (getline(input, line)) {
        stringstream ss(line);

        string classLabel;
        ss >> classLabel;

        if (classLabel == "1.0000000e+000" || classLabel == "1.0000000e+00") {
            numTimesClass1++;
        } 
        else if (classLabel == "2.0000000e+000" || classLabel == "2.0000000e+00"){
            numTimesClass2++;
        }

        vector<double> features;
        string feature;
        int i = 0;
        while(ss >> feature) {
            // used in calculating sums across features
            if(firstInstance) {
                sums.push_back(stod(feature));
            } else {
                sums[i] += stod(feature);
            }

            // used in creating instance at every line (for dataset)
            features.push_back(stod(feature));
            i++;
        }
        firstInstance = 0;
        numFeatures = features.size();

        // adding non-normalized instance to dataset for now
        Instance instance = Instance(instanceID, stod(classLabel), features);
        dataset.push_back(instance);
        instanceID++;
    }
    input.close();

    this->numFeatures = numFeatures;
    if (numTimesClass1 > numTimesClass2) {
        this->sizeOfMostCommonClass = numTimesClass1;
        //printf("Most common class is 1 with %d instances\n", numTimesClass1);
        //printf("Class 2 had %d instances\n", numTimesClass2);
    }
    else {
        this->sizeOfMostCommonClass = numTimesClass2;
        //printf("Most common class is 2 with %d instances\n", numTimesClass2);
        //printf("Class 1 had %d instances\n", numTimesClass1);
    }

    printf("\nThis dataset has %d features (not including the class attribute), with %d instances", this->numFeatures, numTimesClass1 + numTimesClass2);
    printf("\nPlease wait while we normalize the data... ");

    // convert sums into means
    vector<double> means;
    for(int i = 0; i < sums.size(); i++) {
        means.push_back(sums[i]/((double)dataset.size()));
    }

    // calculate standard deviation per feature for normalization
    // using formula s = sqrt((sum(x - mean)^2) / (n - 1)) where x is each value
    vector<double> normalizationSums(numFeatures, 0.0);
    for(int i = 0; i < dataset.size(); i++) {
        for(int j = 0; j < dataset[i].features.size(); j++) {
            normalizationSums[j] += pow(dataset[i].features[j] - means[j], 2);
        }
    }
    vector<double> stdDeviations;
    for(int i = 0; i < normalizationSums.size(); i++) {
        double quotient = normalizationSums[i] / ((double) dataset.size() - 1.0);
        double squareRoot = sqrt(quotient);
        stdDeviations.push_back(squareRoot);
    }

    // normalize feature data in dataset using X = (X - mean(X)) / std(X)
    for(int i = 0; i < dataset.size(); i++) {
        for(int j = 0; j < dataset[i].features.size(); j++) {
            dataset[i].features[j] = (dataset[i].features[j] - means[j]) / stdDeviations[j];
        }
    }
    printf("Done!\n");
    clock_t endTime = clock();
    // printf("Dataset loaded %d instances and %d features in %fms\n", dataset.size(), numFeatures, 1000.0 * (endTime - beginTime) / CLOCKS_PER_SEC);
    this->datasetSize = dataset.size();
}

/**
 * Accuracy function for dataset with all features
 * Determines accuracy of dataset using 1-NN
 * 
 * @returns accuracy as a double in the range [0,1]
*/
double Validator::accuracy() {
    clock_t beginTime = clock();
    // Train classifier based on feature subset
    Classifier classifier = Classifier();
    classifier.train(dataset);

    double correct = 0;
    for(int i = 0; i < dataset.size(); i++) {
        int result = classifier.test(dataset[i]);
        if(result == dataset[i].classLabel) {
            correct++;
        }
    }

    // cout << "hello" << endl;
    clock_t endTime = clock();
    //printf("Accuracy calculated in %fms", 1000.0 * (endTime - beginTime) / CLOCKS_PER_SEC);

    return correct / (double) dataset.size();
}

/**
 * Accuracy function for dataset
 * Determines accuracy of dataset using 1-NN
 * 
 * @param features - vector of feature indices to use for accuracy calculation (null vector uses all features)
 * @returns accuracy as a double in the range [0,1]
*/
double Validator::accuracy(set<int> features) {
    clock_t beginTime = clock();
    // Train classifier based on feature subset
    Classifier classifier = Classifier();
    if(features.size() == 0) {
        // optimization if no features are selected
        classifier.train(vector<Instance>());
        return defaultRate();
    } else {
        // Subset (reduced amount) of dataset to be trained
        vector<Instance> subset;
        for(int i = 0; i < dataset.size(); i++) {
            // Subset of features to be tested
            vector<double> featureSubset;
            // Iterate through wanted features
            /*
            for(int j = 0; j < features.size(); j++) {
                featureSubset.push_back(dataset[i].features[features[j] - 1]);
            }
            */
            for (auto itr = features.begin(); itr != features.end(); itr++) {
                featureSubset.push_back(dataset[i].features[*itr - 1]);
            }
            Instance instance = Instance(dataset[i].id, dataset[i].classLabel, featureSubset);
            subset.push_back(instance);
        }
        classifier.train(subset);
    }
    clock_t trimTime = clock();
    // printf("Dataset trimmed in %fms\n", 1000.0 * (trimTime - beginTime) / CLOCKS_PER_SEC);

    double correct = 0;
    for(int i = 0; i < dataset.size(); i++) {
        // Testing with reduced instance
        vector<double> featureSubset;
        // for(int k = 0; k < features.size(); k++) {
        //     featureSubset.push_back(dataset[i].features[features[k] - 1]);
        // }
        for(auto it = features.begin(); it != features.end(); it++){
            featureSubset.push_back(dataset[i].features[*it - 1]);
        }

        Instance reducedInstance(dataset[i].id, dataset[i].classLabel, featureSubset);
        int result = classifier.test(reducedInstance);
        if(result == dataset[i].classLabel) {
            correct++;
        }
    }

    clock_t endTime = clock();
    // printf("Accuracy calculated in %fms\n", 1000.0 * (endTime - beginTime) / CLOCKS_PER_SEC);

    double quotient = correct / ((double) dataset.size());
    return quotient;
}