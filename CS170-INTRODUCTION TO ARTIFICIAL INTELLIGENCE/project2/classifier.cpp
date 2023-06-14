#include <vector>
#include <cmath>
#include <iostream>
#include <ctime>
#include "classifier.h"
#include "instance.h"

using namespace std;

/**
 * Train data for Classifier class
 * 
 * @param trainingData - vector of instance data
 * @returns void
*/
void Classifier::train(vector<Instance> trainingData) {
    clock_t beginTime = clock();
    trainedData = trainingData;
    clock_t endTime = clock();
    // printf("Data trained in %fms\n", 1000.0 * (endTime - beginTime) / CLOCKS_PER_SEC);
}

/**
 * Tests one instance for class label based on trained data (1-NN)
 * 
 * @param instance - instance to test vs trained data
 * @returns int - resultant class label of instance based on data
*/
int Classifier::test(Instance instance) {
    clock_t beginTime = clock();

    double shortestDistance = INFINITY;
    int classLabel = -1;
    int closestInstanceID = -1;
    
    for(int i = 0; i < trainedData.size(); i++) {
        if(trainedData[i].id == instance.id) {
            continue;
        }

        double distance = 0;
        for(int j = 0; j < trainedData[i].features.size(); j++) {
            double difference = trainedData[i].features[j] - instance.features[j];
            distance += pow(difference, 2);
            
        }
        distance = sqrt(distance);

        if(distance < shortestDistance) {
            shortestDistance = distance;
            classLabel = trainedData[i].classLabel;
            closestInstanceID = trainedData[i].id;
        }
    }

    clock_t endTime = clock();

    // printf("For instance %d, the closest instance is %d with a distance of %f and a class label of %d; tested in %fms\n", instance.id, closestInstanceID, shortestDistance, classLabel, 1000.0 * (endTime - beginTime) / CLOCKS_PER_SEC);

    //cout << "For instance " << instance.id << ", the closest instance is " << closestInstanceID << " with a distance of " << shortestDistance << " and a class label of " << classLabel << endl << endl;

    return classLabel;
}