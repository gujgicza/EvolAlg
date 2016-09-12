
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
    
    // initialise the first column with 0s
    for (int i = 0; i < size; i++)
    {
        matrix[i][0] = 0;
        
    }
    
    // initialise the first row: 0 if the first item does not fit, the value of the first item if it fits
    for (int j = 0; j <= capacity; j++)
    {
        if (things[0].weight <= j){
            matrix[0][j] = things[0].value;
        }
        else matrix[0][j] = 0;
    }
    
    // dynamic programming: get matrix[i][j] given the previous calculated cells
    for (int i = 1; i < size; i++)
    {
        for (int j = 1; j <= capacity; j++)
        {
            if (things[i].weight <= j)
                                        /* if we don't include the item: same as the previous row */
                matrix[i][j] = std::max(matrix[i-1][j],
                                        /* if we include the item: previous row with less capacity plus this item */
                                        things[i].value + matrix[i-1][j - things[i].weight]);
            else
                matrix[i][j] = matrix[i-1][j];
        }
    }
    
    // returns the best option with all the items
    return matrix[things.size()-1][capacity];
}

void BackPack::PrintResult(){
    
    // print the matrix
    for(int i2 = 0; i2 < size; i2++)
    {
        for (int j2 = 0; j2 <= capacity; j2++)
        {
            std::cout << matrix[i2][j2] << " ";
        }
        std::cout << std::endl;
    }
    
    
    // print the selected items
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

