//
//  Network.hpp
//  Neural Network
//
//  Created by Hemanta Pun on 23/07/2016.
//  Copyright © 2016 Hemanta Pun. All rights reserved.
//

#ifndef Network_hpp
#define Network_hpp

#include "Neuron.hpp"
#include <vector>

using namespace std;

typedef vector<Neuron> Layer;

class Network {

private:

    vector<Layer> my_layer;
    double my_error;
    
    
public:

    Network(vector<int> topology);
    void feedforward(const vector<double> &inputs);
    void backPropagation(const vector<double> &actualOutput);
    int getResult();
    double getError(double y);
    
    
    
    
};
#endif /* Network_hpp */
