#include <iostream>
#include "genetic.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <map>

///Random ctor
Entity::Entity(int n){
	std::vector<int> permutations, permHelper;
	for (int i = 0; i < n; ++i){
		int tmp = rand();
		permHelper.push_back(tmp);
		permutations.push_back(tmp);
	}
	std::sort(permHelper.begin(), permHelper.end(), [](int a, int b){return a < b; });
	for (int i = 0; i < n; ++i){
		auto it = std::find(permutations.begin(), permutations.end(), permHelper[i]);
		*it = i;
	}
	fitness = GetValue();
}

Entity::Entity(std::vector<int> gen){
	genotype = gen;
	fitness = GetValue();
}

Entity Entity::CrossOverOX(Entity e){
	int pos1 = rand() % genotype.size(), pos2 = rand() % genotype.size();
	std::cout << pos1 << " " << pos2;
	std::vector<int> childGenotype;
	for (auto i : genotype)
		childGenotype.push_back(-1);

	for (int i = pos1; i <= pos2; ++i)
		childGenotype[i] = genotype[i];

	int lastUsedChildPos = pos2;
	int lastUsedParent2Pos = pos2;
	while (lastUsedChildPos < genotype.size()){

	}
}

int Entity::GetValue(){
	int numberOfConflicts = 0;
	int sizeOfBoard = genotype.size();
	for (int i = 0; i < sizeOfBoard - 1; ++i){
		for (int j = i + 1; j < sizeOfBoard; ++j){
			if ((abs(j - i) - abs(genotype[i] - genotype[j])) < 0.2) // double == is iffy
				numberOfConflicts++;
		}
	}
	return ((sizeOfBoard * (sizeOfBoard + 1)) / 2 - numberOfConflicts) * ((sizeOfBoard * (sizeOfBoard + 1)) / 2 - numberOfConflicts);
}

void Entity::getEntity(){
	for (auto i : genotype)
		std::cout << i << " ";
}

void Entity::Mutate(int mutateChance){
	if ((rand() % 100 + 1) <= mutateChance){
		int pos1 = rand() % genotype.size(), pos2 = rand() % genotype.size();
		int tmp = genotype[pos1];
		genotype[pos1] = genotype[pos2];
		genotype[pos2] = tmp;
	}
}

Population::Population(int n, int mutate, int maxGen, int popSize){
	for (int i = 0; i < popSize; ++i)
		population.push_back({n});
	sizeOfBoard = n;
	mutateChance = mutate;
	maxGenerations = maxGen;
	currentGeneration = 0;
	int prob = population.size() * 5 + 1; //First place gets e.g. 101, second gets 86 and so on.
	int probSum = ((1 + prob) * population.size()) / 2;
	for (int i = 0; i < population.size(); ++i){ //Places the probabilities for each ordinal number in the map
		for (int j = probSum; j > probSum - prob; --j)
			probabilities.insert({ j, i });
		probSum -= prob;
		prob -= 5;
	}
}

void Population::evolve(){
	for (; currentGeneration < maxGenerations; ++currentGeneration){
		popSort();
		auto parents = chooseParents();
		population.clear();
		for (auto& parent : parents){
			population.push_back(parent.first.CrossOverOX(parent.second));
		}
		for (auto& entity : population)
			entity.Mutate(mutateChance);

	}
	popSort();
}

void Population::getPop(){
	int average = 0;
	for (auto e : population)
		average += e.GetValue();
	std::cout << "Best entity's value is: " << population[0].GetValue() << std::endl << "Average value is: " << average / population.size();
	std::cout << std::endl << "Best entity is: ";
	population[0].getEntity();
}

void Population::popSort(){
	std::sort(population.begin(), population.end(), [](Entity e1, Entity e2){return e1.GetValue() > e2.GetValue(); });
}

std::vector<std::pair<Entity, Entity>> Population::chooseParents(){
	int prob = population.size() * 5 + 1;
	int probSum = ((1 + prob) * population.size()) / 2;
	std::vector<std::pair<Entity, Entity>> retVal;
	for (int i = 0; i < population.size(); ++i)
		retVal.push_back({ population[probabilities.at(rand() % probSum)], population[probabilities.at(rand() % probSum)] }); //Relatively even distribution with %
	return retVal;
}