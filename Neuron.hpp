//
//  Neuron.hpp
//  Neural Network
//
//  Created by Hemanta Pun on 23/07/2016.
//  Copyright © 2016 Hemanta Pun. All rights reserved.
//

#ifndef Neuron_hpp
#define Neuron_hpp

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <cstdint>

using namespace std;


class Neuron;

typedef vector<Neuron> Layer;

class Neuron {
private:
    double output;
    double signal;
    vector<double> inputs;
    vector<double> weights;
    int indexNum;
    double eta;
    double delta;
    
    
    static double random(double min, double max);
    double activationFunction(double x);
    double activationFunctionDerivative(double x);
    
    
    
public:

    Neuron(const int &numOutputs, const int &num);
    void setOutputVal(double val);
    double getOutputVal();
    void feedforward(Layer &prevLayer);
    void calcHiddenDelta(Layer &nextLayer);
    void updateWeights(Layer &layer,Layer &nextLayer);
    void calcDeltaOutput(double actual);
    void getResult();
    void setDelta(double d);
    double getDelta();

    
};

#endif /* Neuron_hpp */
