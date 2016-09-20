//
//  Network.cpp
//  Neural Network
//
//  Created by Hemanta Pun on 23/07/2016.
//  Copyright © 2016 Hemanta Pun. All rights reserved.
//

#include "Network.hpp"
#include <iostream>

Network::Network(vector<int> topology) {
    for( int layerNum = 0; layerNum< topology.size(); layerNum++)
    {
        my_layer.push_back(Layer());
        int numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum+1];
        for(int neuronNum = 0; neuronNum <= topology[layerNum]; neuronNum++)
        {
            my_layer.back().push_back(Neuron(numOutputs, neuronNum));
        }
        my_layer.back().back().setOutputVal(1.0);
        my_layer.back().back().setDelta(0.0);
    }
}

void Network:: feedforward(const vector<double> &inputs)
{
//    cout<<"-----------------FORWARD PROPAGATION -------------\n";
//    cout<<"layer 0 \n";
    for(int i = 0; i < inputs.size(); i++)
    {
//        cout<<"neuron :"<<i<<" value: "<<inputs[i]<<endl;
        my_layer[0][i].setOutputVal(inputs[i]);
    }
    
    for(int layer = 1; layer < my_layer.size();layer++)
    {
        Layer prevLayer = my_layer[layer -1];
//        cout<<"\nlayer "<<layer;
        
        for(int n = 0; n < my_layer[layer].size() -1 ;n++ )
        {
//            cout<<"\nneuron "<< n<<endl;
            my_layer[layer][n].feedforward(prevLayer);
        }
    }    
}



void Network:: backPropagation(const vector<double> &actualOutput)
{
//    cout<<"\n------------BACK PROPAGATION--------------------\n";
    Layer &outputLayer = my_layer.back();

    //Calculate delta for output layer
    for(int i = 0; i< outputLayer.size() -1 ;i++)
    {
        outputLayer[i].calcDeltaOutput(actualOutput[i]);
    }
//    cout<<"-----------"<<endl;

    //Calculate delta for hidden layers
    
    for(int layerNum = my_layer.size() - 2; layerNum > 0; layerNum--)
    {
        Layer &hiddenLayer = my_layer[layerNum];
        Layer &nextLayer = my_layer[layerNum + 1];

//        cout<<"\nLayer "<<layerNum;
        for(int i = 0 ; i<hiddenLayer.size() - 1; i++)
        {
            hiddenLayer[i].calcHiddenDelta(nextLayer);
        }
    }
   
    //Update Weights
//    cout<<"\n\nAdjust weights";
    for(int layerNum = my_layer.size()-2; layerNum >= 0; --layerNum)
    {
        Layer &layer = my_layer[layerNum];
        Layer &nextLayer = my_layer[layerNum + 1];
        
//        cout<<"\n\nLayer"<<layerNum;
        for(int n = 0; n<layer.size() ; ++n)
        {
//            cout<<"\nNeuron no: "<<n;
            layer[n].updateWeights(layer, nextLayer);
        }
    }
}

int Network:: getResult()
{
    int res;
    vector<double> v;
//    cout<<" \nOUTPUT :"<<endl;
    for(int i = 0; i< my_layer.back().size()-1; ++i)
    {
//        cout<<i<<" : "<<my_layer.back()[i].getOutputVal()<<endl;
        v.push_back(my_layer.back()[i].getOutputVal());
    }
    auto b = max_element(begin(v), end(v));
    res = distance(begin(v), b);
//    cout<<"OUTPUT------------------------ "<<res<<endl;
//    cout<<my_layer.back()[0].getOutputVal();
    return res;
}

double Network:: getError(double y)
{
//    cout<<"Y "<< y << "   "<< my_layer.back()[0].getOutputVal()<<endl;
    return (y - my_layer.back()[0].getOutputVal()) ;
}















