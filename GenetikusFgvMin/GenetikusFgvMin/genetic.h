#include <vector>
#include <map>

using namespace std;

class Entity {
    vector<bool> genotype; //x in binary
    // bool genotype[18];   // -> 10^5<2^17
    int fenotype;           // value of x
    
public:
    Entity(int);
    void convertToGray();
    int getFitness();
    void mutate();
    pair<Entity, Entity> crossOverUniform(Entity);
    
};

class Population {
    vector<Entity> population; // the entities
    int mutateChanche;
    int maxGenerations;
    int currentGeneration;
    map<int, int> probabilties;
    
public:
    Population(int mutate, int maxGen, int popSize);
    void evolve();
    void getPop();
    void popSort();
    vector<pair<Entity, Entity>> chooseParents();
};
