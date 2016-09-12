
#ifndef backpack_hpp
#define backpack_hpp

#include <stdio.h>
#include <vector>

/* class for things you can pack in the backpack. */
class Thing{
public:
    int value;
    int weight;
    Thing(int, int);
};

/* class for algorithm
 * stores list and number of things, bag size
 * and a matrix for the algorithm
 */
class BackPack{
    std::vector<Thing> things;
    int size;
    int capacity;
    int** matrix;
    
public:
    
    BackPack(std::vector<Thing>, int capacity);
    
    /// calculates the matrix values
    int Calculate();
    
    /// print the selected items' number
    void PrintResult();
    
};


#endif /* backpack_hpp */
