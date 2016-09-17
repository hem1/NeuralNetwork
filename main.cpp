//
//  main.cpp
//  Neural Network
//
//  Created by Hemanta Pun on 23/07/2016.
//  Copyright © 2016 Hemanta Pun. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>

#include "Network.hpp"
#include "Neuron.hpp"
#include "MNIST_data.hpp"

using namespace std;

void test_xor(Network &mynetwork)
{
    cout<<"enter two numbers ";
    int a, b;
    while(cin)
    {
        cin>> a;
        cin>>b;
        mynetwork.feedforward({(double)a,(double)b});
        cout<< " actual is "<<(a xor b)<<endl;
        mynetwork.getResult();
        
        cout<<"ERROR "<<mynetwork.getError((a xor b))<<endl;
        cout<<"enter two numbers ";
        
    }
}

void train_xor_fm_file()
{
    vector<int> topology;
    topology.push_back(2);
    topology.push_back(4);
    topology.push_back(1);
    
    Network mynetwork(topology);
    mynetwork.getResult();
    
    vector<double> inputs;
    vector<double> actualOutput;
    
    
    ifstream infile("out_xor.txt");
    string s;
    
    while(getline(infile, s))
    {
        int pass = 0;
        int index = 0;
        while(s[index] != ':') index++;
        
        if(s.substr(0,index).compare( "in" ) == 0)
        {
            string ss = s.substr(index+2);
            int i = 0;
            while(ss[i] != ' ') i++;
            double x = stod(ss.substr(0,i));
            double y = stod(ss.substr(i));
            
            cout<<x<<" and "<<y<<endl;
            mynetwork.feedforward({x,y});
        }
        
        else if(s.substr(0,index).compare( "out" ) == 0)
        {
            double z = stod(s.substr(index+2));
            cout<<"out is "<<z<<endl;
            mynetwork.backPropagation({z});
            if(pass++ >100  && abs(mynetwork.getError(z)) <0.05)
            {
                break;
            }
        }
    }
    test_xor(mynetwork);
    
}

void train_xor_rand_input()
{
    vector<int> topology;
    topology.push_back(2);
    topology.push_back(4);
    topology.push_back(1);
    
    Network mynetwork(topology);
    
    vector<double> inputs;
    vector<double> actualOutput;
    
    srand(time(0));
    int i = 0;
    cout<<"processing......\n";
    while(1)
    {
        
        int x = rand() % 2;
        int y = rand() % 2;
        int z = (x xor y);
        actualOutput.push_back(double (x));
        actualOutput.push_back(double (y));
        
        mynetwork.feedforward(actualOutput);
        actualOutput.clear();
        mynetwork.backPropagation({(double)z});
        
        cout << "pass "<<i<<endl;
        cout<<"\n--------------------x "<<x<<" y "<<y<<endl;
        cout<<"ACTUALLLLLLL "<< z;
        mynetwork.getResult();
        cout<<"Error "<<mynetwork.getError((double)z)<<endl;
        cout<<"---------------------------------\n";
        
        if(i++ >100  && abs(mynetwork.getError((double)z)) < 0.05)
        {
            break;
        }
    }
    cout<<"\nepoch is \n"<<i<<endl;
    test_xor(mynetwork);

}

void train_images()
{
    vector<int> topology;
    topology.push_back(784);
    topology.push_back(300);
    topology.push_back(10);
    
    Network mynetwork(topology);
    
    
    vector<vector<double>> training_images;
    vector<double> training_labels;
    vector<vector<double>> test_images;
    vector<double> test_labels;
    
    readImages("train-images-idx3-ubyte", training_images);
    readLabels("train-labels-idx1-ubyte", training_labels);
    
    //    cout<<training_labels.size()<<endl;
    //    cout<<training_images.size()<<endl;
    cout<<"processing...\n";
    for(int i = 0; i< 60000; i++)
    {
//        cout<<"Actual label is "<<training_labels[i];
        mynetwork.feedforward(training_images[i]);
//        mynetwork.getResult();
        vector<double> v(10 , 0.0);
        v[training_labels[i]] = 1.0;
        mynetwork.backPropagation(v);
//        cout<<endl;
        v.clear();
    }
    
    readImages("test_set-images-idx3-ubyte", test_images);
    readLabels("test_set-labels-idx1-ubyte", test_labels);
    
    int count = 0;
    for(int i = 0; i< 10000; i++)
    {
        mynetwork.feedforward(test_images[i]);
        int res = mynetwork.getResult();
//        cout<<"actual label is "<<test_labels[i]<<" \t output is "<<res<<endl;
        if(res != test_labels[i]) count++;
    }
    cout<<"number of wrong classification is "<<count<<endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
//    train_xor_rand_input();
    
    train_images();
    
    
    return 0;
}
