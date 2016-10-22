#include <vector>
#include <map>

class Entity{

	std::vector<int> genotype; //The permutation
	int fitness;


public:

	Entity(int);
	Entity(std::vector<int>);

	Entity CrossOverOX(Entity);
	int GetValue();
	void Mutate(int);
	void getEntity();
};

class Population{

	int sizeOfBoard; //The size of the board
	std::vector<Entity> population; //The entities
	int mutateChance;
	int maxGenerations;
	int currentGeneration;
	std::map<int, int> probabilities; //Used in selecting the parents, stores the probabilities assigned to each ordinal number based on fitness

public:

	Population(int n, int mutate, int maxGen, int popSize);

	void evolve();
	void getPop();
	void popSort();
	std::vector<std::pair<Entity, Entity>> chooseParents();
};