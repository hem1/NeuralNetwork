//
//  MNIST_data.hpp
//  Neural Network
//
//  Created by Hemanta Pun on 08/09/2016.
//  Copyright © 2016 Hemanta Pun. All rights reserved.
//

#ifndef MNIST_data_hpp
#define MNIST_data_hpp


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int reverseInt (int i);
void readLabels(string fileName, vector<double> &vec);
void readImages(string fileName, vector<vector<double>> &vec);

#endif /* MNIST_data_hpp */
