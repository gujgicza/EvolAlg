#include <vector>
#include <map>

class Entity{

	std::vector<bool> genotype; //Which objects are put in the bag
	std::vector<std::pair<int, int>> fenotype; //Weight, Value
	int capacity; //The bag's capacity


public:

	Entity(std::vector<std::pair<int, int>>, int);
	Entity(std::vector<bool>, std::vector<std::pair<int, int>>, int);

	std::pair<Entity, Entity> CrossOverUniform(Entity);
	int GetValue();
	void Mutate(int);
};

class Population{

	std::vector<std::pair<int, int>> objects; //The objects that we're trying to fit into the bag
	std::vector<Entity> population; //The entities
	int capacity;
	int mutateChance;
	int maxGenerations;
	int currentGeneration;
	std::map<int, int> probabilities; //Used in selecting the parents, stores the probabilities assigned to each ordinal number based on fitness

public:

	Population(std::vector<std::pair<int, int>> objects, int capacity, int mutate, int maxGen, int popSize);

	void evolve();
	void getPop();
	void popSort();
	std::vector<std::pair<Entity, Entity>> chooseParents();
};