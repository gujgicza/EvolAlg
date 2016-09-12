
#include <iostream>
#include "backpack.hpp"

int main(int argc, const char * argv[]) {
    
    // first param: value, second param: weight
    Thing t1(7, 4);
    Thing t2(5, 6);
    Thing t3(3, 3);
    Thing t4(1, 2);
    
    // last parameter is the capacity
    BackPack bp { std::vector<Thing> {t1, t2, t3, t4}, 8};
    
    bp.Calculate();
    bp.PrintResult();
    
    getchar();
    return 0;
}
