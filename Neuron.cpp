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
    eta = 0.25+0.005;
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
    return 1/(1+exp(-x));
}

double Neuron::activationFunctionDerivative(double s)
{
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
//        cout<< "o : "<<prevLayer[i].getOutputVal() << "  w :"<<prevLayer[i].weights[i]<<endl;
    }
    signal = sum;
    output = activationFunction(sum);
//    cout<< " sum :"<<signal<<" output :"<<output<<endl;

   
}
void Neuron:: calcDeltaOutput(double actual)
{
    
//    delta = (output - actual)* activationFunctionDerivative(output);
//    cout<<"output layer\n";
//    cout<<"output "<<output<<endl;
//    cout<<(actual-output)<<" "<< activationFunctionDerivative(output)<<" delta : "<<delta<<endl;
    double e = (actual-output);
//    cout<<"error "<<e<<endl;
    delta = e * activationFunctionDerivative(output);
//    cout<<"delta "<<delta<<"     "<<"out "<<output<<"      actual "<<actual<<endl;
//    cout<<"e : "<<e;
//    cout<<" out is "<<output<<endl;

    
}


void Neuron:: calcHiddenDelta(Layer &nextLayer)
{
    double sum = 0.0;

    for(int i = 0 ; i< nextLayer.size()-1; ++i)
    {
        sum += weights[i] * nextLayer[i].delta;
//        cout<< "d "<<nextLayer[i].delta<< " w :"<<weights[i];
    }
//    cout<<" o :"<<output<<endl;
    
    delta = sum * activationFunctionDerivative(output);
//    cout<<"\nDelta :"<< delta<<endl;
    
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
    
    
    
    
    
    
    
    
    
    
    
    
