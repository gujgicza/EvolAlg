//
//  backpack.hpp
//  Hatizsak
//
//  Created by Anna Gujgiczer on 9/12/16.
//  Copyright © 2016 Anna Gujgiczer. All rights reserved.
//

#ifndef backpack_hpp
#define backpack_hpp

#include <stdio.h>
#include <vector>

class Thing{
public:
    int value;
    int weight;
};

class BackPack{
    std::vector<Thing> things;
    int size;
    int capacity;
    int doStep(int, int);
    int** matrix;
    
public:
    
    BackPack(std::vector<Thing>, int capacity);
    
    int Calculate();
    
    void PrintResult();
    
};


#endif /* backpack_hpp */
