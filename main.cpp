//
//  main.cpp
//  Neural Network
//
//  Created by Hemanta Pun on 23/07/2016.
//  Copyright © 2016 Hemanta Pun. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <string>
#include <vector>

#include "Neuron.hpp"
#include "Network.hpp"
#include "MNIST_data.hpp"


using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    vector<int> topology;
    topology.push_back(784);
    topology.push_back(100);
    topology.push_back(10);
    
    Network mynetwork(topology);

    vector<vector<double>> training_images;
    vector<double> training_labels;
    vector<vector<double>> test_images;
    vector<double> test_labels;
      
    readImages("train-images-idx3-ubyte", training_images);
    readLabels("train-labels-idx1-ubyte", training_labels);
        

    cout<<"processing...\n";
    for(int i = 0; i< 60000; i++)
    {

        mynetwork.feedforward(training_images[i]);
        vector<double> v(10 , 0.0);
        v[training_labels[i]] = 1.0;
        mynetwork.backPropagation(v);
        v.clear();
    }
    training_images.clear();
    training_labels.clear();
        
    readImages("test_set-images-idx3-ubyte", test_images);
    readLabels("test_set-labels-idx1-ubyte", test_labels);
        
    int count = 0;
    for(int i = 0; i< 10000; i++)
    {
        mynetwork.feedforward(test_images[i]);
        int res = mynetwork.getResult();

        if(res != test_labels[i]) count++;
    }
    cout<<"number of wrong classification is "<<count<<endl;
   
    return 0;
}
