#include <iostream>
#include "genetic.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>

Entity::Entity(std::vector<std::pair<int, int>> objects, int cap){
	fenotype = objects;
	for (auto a : fenotype){
		if ((rand() % 2) == 0)
			genotype.push_back(true);
		else
			genotype.push_back(false);
	}
	capacity = cap;
}

Entity::Entity(std::vector<bool> geno, std::vector<std::pair<int, int>> feno, int cap){
	fenotype = feno;
	genotype = geno;
	capacity = cap;
}

std::pair<Entity, Entity> Entity::CrossOverUniform(Entity e){
	std::vector<bool> childOneGenotype, childTwoGenotype;
	for (int i = 0; i < fenotype.size(); ++i){
		if ((rand() % 2) == 0){
			childOneGenotype.push_back(genotype[i]);
			childTwoGenotype.push_back(e.genotype[i]);
		}
		else{
			childOneGenotype.push_back(e.genotype[i]);
			childTwoGenotype.push_back(genotype[i]);
		}
	}

	return std::pair < Entity, Entity > {{ childOneGenotype, fenotype, capacity },{ childTwoGenotype, fenotype, capacity }};
}

int Entity::GetValue(){
	int retVal = 0;
	int weight = 0;
	for (int i = 0; i < fenotype.size(); ++i)
		if (genotype[i])
			weight += fenotype[i].first;
	if (weight <= capacity){
		for (int i = 0; i < fenotype.size(); ++i)
			if (genotype[i])
				retVal += fenotype[i].second;
		return retVal;
	}
	return capacity - weight;
}

void Entity::Mutate(int mutateChance){
	for (auto& gene : genotype)
		if ((rand() % 100 + 1) <= mutateChance)
			gene = !gene;
}

Population::Population(std::vector<std::pair<int, int>> objectValues, int Capacity, int mutate, int maxGen, int popSize){
	objects = objectValues;
	for (int i = 0; i < popSize; ++i)
		population.push_back({ objectValues, Capacity });
	capacity = Capacity;
	mutateChance = mutate;
	maxGenerations = maxGen;
	currentGeneration = 0;
}

void Population::evolve(){
	for (; currentGeneration < maxGenerations; ++currentGeneration){
		popSort();
		auto parents = chooseParents();
		population.clear(); //????
		for (auto& parent : parents){
			auto children = parent.first.CrossOverUniform(parent.second);
			population.push_back(children.first);
			population.push_back(children.second);
		}
		for (auto& entity : population)
			entity.Mutate(mutateChance);

	}
}

void Population::getPop(){
	//todo
}

void Population::popSort(){
	std::sort(population.begin(), population.end(), [](Entity e1, Entity e2){return e1.GetValue() > e2.GetValue(); });
}

std::vector<std::pair<Entity, Entity>> Population::chooseParents(){
	//todo
}