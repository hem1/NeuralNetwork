//
//  Neuron.cpp
//  Neural Network
//
//  Created by Hemanta Pun on 23/07/2016.
//  Copyright © 2016 Hemanta Pun. All rights reserved.
//

#include "Neuron.hpp"

Neuron::Neuron(const int &numOutputs, const int &num)
{
    output = 0.0;
    eta = 0.25;
    
    for(int i = 0; i< numOutputs; i++)
    {
        weights.push_back(random( -1.0 , 1.0));
//        weights.push_back(rand() / double(RAND_MAX));
    }
    indexNum = num;
}

double Neuron:: random(double min, double max)
{
    return (min + (rand()/ (RAND_MAX /(max-min) )));
//    return (min + (rand() / ((int)(max-min) )));
}

void Neuron::setOutputVal(double val)
{
    output = val;
}

double Neuron::getOutputVal()
{
    return output;
}

double Neuron::activationFunction(double x)
{
//    return tanh(x);
    //sigmoid 
    return 1/(1+exp(-x));
}

double Neuron::activationFunctionDerivative(double s)
{
    //for tanh(x)
//    return (1 - s*s);
    //for sigmoid
    return (s)*(1-s);
}

void Neuron:: setDelta(double d)
{
    delta = d;
}
double Neuron:: getDelta()
{
    return delta;
}
void Neuron::feedforward(Layer &prevLayer)
{
    double sum = 0;
    
    for( int i = 0; i< prevLayer.size();i++)
    {
        sum += prevLayer[i].getOutputVal()* prevLayer[i].weights[indexNum] ;
    }
    signal = sum;
    output = activationFunction(sum);
}

void Neuron:: calcDeltaOutput(double actual)
{    
    double e = (actual-output);
    
    delta = e * activationFunctionDerivative(output);
}

void Neuron:: calcHiddenDelta(Layer &nextLayer)
{
    double sum = 0.0;

    for(int i = 0 ; i< nextLayer.size()-1; ++i)
    {
        sum += weights[i] * nextLayer[i].delta;
    }    
    delta = sum * activationFunctionDerivative(output);    
}

void Neuron:: updateWeights(Layer &layer, Layer &nextLayer)
{
    for(int n = 0; n < nextLayer.size() - 1; ++n)
    {
        weights[n] += (eta * output * nextLayer[n].delta);
    }
}

void Neuron:: getResult()
{
    for(int w=0; w< weights.size(); ++w)
    {
        cout<<" weight "<< weights[w];
        cout<<" delta "<<delta<<endl;
    }
    cout<<endl;
}
    
    
    
    
    
    
    
    
    
    
    
    
