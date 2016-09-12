//
//  backpack.cpp
//  Hatizsak
//
//  Created by Anna Gujgiczer on 9/12/16.
//  Copyright © 2016 Anna Gujgiczer. All rights reserved.
//

#include "backpack.hpp"
#include <iostream>

Thing::Thing(int val, int w){
    value = val;
    weight = w;
}


BackPack::BackPack(std::vector<Thing> params, int capacity){
    this->things = params;
    this->capacity = capacity;
    size = (int)params.size();
    
    matrix = new int*[size];
    
    for (int i = 0; i < size; i++ ){
        matrix[i] = new int[capacity + 1];
    }
    
    
}

int BackPack::Calculate(){
    
    for (int i = 0; i < size; i++)
    {
        matrix[i][0] = 0;
        
    }
    
    for (int j = 0; j <= capacity; j++)
    {
        if (things[0].weight <= j){
            matrix[0][j] = things[0].value;
        }
        else matrix[0][j] = 0;
    }
    
    for (int i = 1; i < size; i++)
    {
        for (int j = 1; j <= capacity; j++)
        {
            if (things[i].weight <= j)
                matrix[i][j] = std::max(matrix[i-1][j], things[i].value + matrix[i-1][j - things[i].weight]);
            else
                matrix[i][j] = matrix[i-1][j];
        }
    }
    
    return matrix[things.size()-1][capacity];
}

void BackPack::PrintResult(){
    
    // matrix
    for(int i2 = 0; i2 < size; i2++)
    {
        for (int j2 = 0; j2 <= capacity; j2++)
        {
            std::cout << matrix[i2][j2] << " ";
        }
        std::cout << std::endl;
    }
    
    int i = size - 1;
    int j = capacity;
    
    while(i >= 0 && j >= 0 && matrix[i][j] > 0){
        while (i >= 1 && matrix[i][j] == matrix[i-1][j]){
                i -= 1;
        }
        
        std::cout << i << std::endl;
        
        j -= things[i].weight;
        i -= 1;
    }
    
}

