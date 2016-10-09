#include <vector>
#include <map>

using namespace std;

class Entity {
    vector<bool> genotype; //x in binary
    // bool genotype[18];   // -> 10^5<2^17
    int fenotype;           // value of x
    
public:
    Entity(int, bool);
    Entity(vector<bool>);
    void convertToGray();
    int getFitness();
    int getFenotype();
    void mutate(int);
    pair<Entity, Entity> crossOverUniform(Entity);
    
};

class Population {
    vector<Entity> population; // the entities
    int mutateChance;
    int maxGenerations;
    int currentGeneration;
    map<int, int> probabilities;
    
public:
    Population(int mutate, int maxGen, int popSize, bool gray);
    void evolve();
    void getPop();
    void popSort();
    vector<pair<Entity, Entity>> chooseParents();
};
