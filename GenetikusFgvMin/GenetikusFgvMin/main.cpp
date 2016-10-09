//
//  main.cpp
//  GenetikusFgvMin
//
//  Created by Anna Gujgiczer on 2016/10/08.
//  Copyright © 2016 Anna Gujgiczer. All rights reserved.
//

#include <iostream>
#include <vector>
#include "genetic.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    int mutateChance, maxGen, popSize;
    cin >> mutateChance >> maxGen >> popSize;

    Population pop{ mutateChance, maxGen, popSize };
    pop.evolve(); //All the fun stuff happens here
    std::cout << std::endl;
    pop.getPop();
    
}
