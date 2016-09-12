//
//  main.cpp
//  Hatizsak
//
//  Created by Anna Gujgiczer on 9/12/16.
//  Copyright © 2016 Anna Gujgiczer. All rights reserved.
//

#include <iostream>
#include "backpack.hpp"

int main(int argc, const char * argv[]) {
    
    Thing t1(6, 4);
    Thing t2(5, 3);
    Thing t3(3, 2);
    Thing t4(3, 2);
    
    BackPack bp { std::vector<Thing> {t1, t2, t3, t4}, 8};
    
    bp.Calculate();
    bp.PrintResult();
    
    getchar();
    
    return 0;
}
