#include <vector>

class Entity{

	std::vector<bool> genotype;
	std::vector<std::pair<int, int>> fenotype; //Weight, Value
	int capacity;

public:

	Entity(std::vector<std::pair<int, int>>, int);
	Entity(std::vector<bool>, std::vector<std::pair<int, int>>, int);

	std::pair<Entity, Entity> CrossOverUniform(Entity);
	int GetValue();
	void Mutate(int);
};

class Population{

	std::vector<std::pair<int, int>> objects;
	std::vector<Entity> population;
	int capacity;
	int mutateChance;
	int maxGenerations;
	int currentGeneration;

public:

	Population(std::vector<std::pair<int, int>> objects, int capacity, int mutate, int maxGen, int popSize);

	void evolve();
	void getPop();
	void popSort();
	std::vector<std::pair<Entity, Entity>> chooseParents();
};