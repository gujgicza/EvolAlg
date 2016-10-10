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
    
    int mutateChance, maxGen, popSize, gray;
    cin >> mutateChance >> maxGen >> popSize >> gray;

    Population pop{ mutateChance, maxGen, popSize, static_cast<bool>(gray)};
    pop.evolve(); //All the fun stuff happens here
    std::cout << std::endl;
    //pop.getPop();
    
}
