//
//  MNIST_data.cpp
//  Neural Network
//
//  Created by Hemanta Pun on 08/09/2016.
//  Copyright © 2016 Hemanta Pun. All rights reserved.
//

#include "MNIST_data.hpp"

int reverseInt (int i)
{
    unsigned char ch1, ch2, ch3, ch4;
    ch1=i&255;
    ch2=(i>>8)&255;
    ch3=(i>>16)&255;
    ch4=(i>>24)&255;
    return((int)ch1<<24)+((int)ch2<<16)+((int)ch3<<8)+ch4;
}

void readLabels(string fileName, vector<double> &vec)
{
    ifstream fin(fileName);
    uint32_t magic_number;
    uint32_t num_of_items;
    fin.read((char*)&magic_number, sizeof(magic_number));
//    cout<<magic_number<<endl;
    fin.read((char*)&num_of_items, sizeof(num_of_items));
//    cout<<num_of_items;
    
    unsigned char temp;
    while(fin.read((char*)&temp, sizeof(temp)))
    {
        vec.push_back(double(temp));
//        cout<<int(temp)<<endl;
    }
    fin.close();
}

void readImages(string fileName, vector<vector<double>> &vec)
{
    ifstream fin(fileName);
    uint32_t magic_number;
    uint32_t num_of_items;
    uint32_t num_of_rows;
    uint32_t num_of_cols;
    
    
    fin.read((char*)&magic_number, sizeof(magic_number));
    magic_number = reverseInt(magic_number);
//    cout<<magic_number<<endl;
    fin.read((char*)&num_of_items, sizeof(num_of_items));
    num_of_items = reverseInt(num_of_items);
//    cout<<"num of items "<<num_of_items<<endl;
    fin.read((char*)&num_of_rows, sizeof(num_of_rows));
    num_of_rows = reverseInt(num_of_rows);
//    cout<<num_of_rows<<endl;
    fin.read((char*)&num_of_cols, sizeof(num_of_cols));
    num_of_cols = reverseInt(num_of_cols);
//    cout<<num_of_cols<<endl;
    
    vector<double> tmp;
    for(int n=0; n< num_of_items; n++)
    {
        for(int r=0; r<num_of_rows; r++)
        {
            for(int c=0; c<num_of_cols; c++)
            {
                unsigned char temp;
                fin.read((char*)&temp,sizeof(temp));
//                tmp.push_back((double)temp);
                tmp.push_back(((double)temp == 0.0) ? 0.0 : double(temp)/255.0);
                
            }
        }
        vec.push_back(tmp);
        tmp.clear();
    }
    fin.close();
}

