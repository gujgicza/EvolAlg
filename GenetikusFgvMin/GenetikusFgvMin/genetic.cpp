//#include <iostream>
//#include "genetic.h"
//#include <ctime>
//#include <cstdlib>
//#include <algorithm>
//#include <map>
//
/////Random ctor
//Entity::Entity(std::vector<std::pair<int, int>> objects, int cap){
//	fenotype = objects;
//	for (auto a : fenotype){
//		if ((rand() % 2) == 0)
//			genotype.push_back(true);
//		else
//			genotype.push_back(false);
//	}
//	capacity = cap;
//}
//
//Entity::Entity(std::vector<bool> geno, std::vector<std::pair<int, int>> feno, int cap){
//	fenotype = feno;
//	genotype = geno;
//	capacity = cap;
//}
//
//std::pair<Entity, Entity> Entity::CrossOverUniform(Entity e){
//	std::vector<bool> childOneGenotype, childTwoGenotype;
//	for (int i = 0; i < fenotype.size(); ++i){
//		if ((rand() % 2) == 0){
//			childOneGenotype.push_back(genotype[i]);
//			childTwoGenotype.push_back(e.genotype[i]);
//		}
//		else{
//			childOneGenotype.push_back(e.genotype[i]);
//			childTwoGenotype.push_back(genotype[i]);
//		}
//	}
//
//	return std::pair < Entity, Entity > {{ childOneGenotype, fenotype, capacity },{ childTwoGenotype, fenotype, capacity }};
//}
//
//int Entity::GetValue(){
//	int retVal = 0;
//	int weight = 0;
//	for (int i = 0; i < fenotype.size(); ++i)
//		if (genotype[i])
//			weight += fenotype[i].first;
//	if (weight <= capacity){
//		for (int i = 0; i < fenotype.size(); ++i)
//			if (genotype[i])
//				retVal += fenotype[i].second;
//		return retVal;
//	}
//	return capacity - weight;
//}
//
//void Entity::Mutate(int mutateChance){
//	for (auto& gene : genotype)
//		if ((rand() % 100 + 1) <= mutateChance)
//			gene = !gene;
//}
//
//Population::Population(std::vector<std::pair<int, int>> objectValues, int Capacity, int mutate, int maxGen, int popSize){
//	objects = objectValues;
//	for (int i = 0; i < popSize; ++i)
//		population.push_back({ objectValues, Capacity });
//	capacity = Capacity;
//	mutateChance = mutate;
//	maxGenerations = maxGen;
//	currentGeneration = 0;
//	int prob = population.size() * 5 + 1; //First place gets e.g. 101, second gets 86 and so on.
//	int probSum = ((1 + prob) * population.size()) / 2;
//	for (int i = 0; i < population.size(); ++i){ //Places the probabilities for each ordinal number in the map
//		for (int j = probSum; j > probSum - prob; --j)
//			probabilities.insert({ j, i });
//		probSum -= prob;
//		prob -= 5;
//	}
//}
//
//void Population::evolve(){
//	for (; currentGeneration < maxGenerations; ++currentGeneration){
//		popSort();
//		auto parents = chooseParents();
//		population.clear();
//		for (auto& parent : parents){
//			auto children = parent.first.CrossOverUniform(parent.second);
//			population.push_back(children.first);
//			population.push_back(children.second);
//		}
//		for (auto& entity : population)
//			entity.Mutate(mutateChance);
//
//	}
//	popSort();
//}
//
//void Population::getPop(){
//	int average = 0;
//	for (auto e : population)
//		average += e.GetValue();
//	std::cout << "Best entity's value is: " << population[0].GetValue() << std::endl << "Average value is: " << average / population.size();
//}
//
//void Population::popSort(){
//	std::sort(population.begin(), population.end(), [](Entity e1, Entity e2){return e1.GetValue() > e2.GetValue(); });
//}
//
//std::vector<std::pair<Entity, Entity>> Population::chooseParents(){
//	int prob = population.size() * 5 + 1;
//	int probSum = ((1 + prob) * population.size()) / 2;
//	std::vector<std::pair<Entity, Entity>> retVal;
//	for (int i = 0; i < population.size() / 2; ++i)
//		retVal.push_back({ population[probabilities.at(rand() % probSum)], population[probabilities.at(rand() % probSum)] }); //Relatively even distribution with %
//	return retVal;
//}
