#include <iostream>
#include "genetic.h"
#include <math.h>
#include <fstream>
#include <algorithm>


Entity::Entity(int x, bool gray){
    fenotype = x;
    while ( genotype.size() < 17) {
        if (x % 2) {
            genotype.insert(genotype.begin(), true);
            x -= 1;
            x /= 2;
        }
        else {
            genotype.insert(genotype.begin(), false);
            x /= 2;
        }
    }
    if (gray)
        convertToGray();
}

Entity::Entity(vector<bool> geno) {
    genotype = geno;
    fenotype = 0;
    for (int i = 0; i < geno.size(); i++) {
        if (geno.back())
            fenotype += pow(2, i);
        geno.pop_back();
    }
}

void Entity::convertToGray() {
    bool prev = genotype.front();
    bool tmp;
    for (int i = 1; i < genotype.size(); i++) {
        tmp = genotype[i];
        if (genotype[i] != prev)
            genotype[i] = 1;
        else
            genotype[i] = 0;
        prev = tmp;
    }
}

int Entity::getFitness() {
    return 400-(fenotype*fenotype);
}

int Entity::getFenotype() {
    return fenotype;
}

void Entity::mutate(int chance) {
    for (auto& gene : genotype)
        if ((rand() % 100 + 1) <= chance)
            gene = !gene;
}

pair<Entity, Entity> Entity::crossOverUniform(Entity e){
    vector<bool> childOneGenotype, childTwoGenotype;
    for (int i = 0; i < genotype.size(); i++){
        if ((rand() % 2) == 0){
            childOneGenotype.push_back(genotype[i]);
            childTwoGenotype.push_back(e.genotype[i]);
        }
        else{
            childOneGenotype.push_back(e.genotype[i]);
            childTwoGenotype.push_back(genotype[i]);
        }
    }
    
    return pair < Entity, Entity > {{ childOneGenotype },{ childTwoGenotype }};
}


Population::Population(int mutate, int maxGen, int popSize, bool gr) {
    mutateChance = mutate;
    maxGenerations = maxGen;
    currentGeneration = 0;
    gray = gr;
    for (int i = 0; i < popSize; i++) {
        population.push_back(Entity {rand() % 100000 + 1, gray});
    }
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
    ofstream os = ofstream();
    if (gray)
        os.open("averagesGray.txt");
    else
        os.open("averages.txt");
    
	for (; currentGeneration < maxGenerations; ++currentGeneration){
		popSort();
        getPop(os);
		auto parents = chooseParents();
		population.clear();
		for (auto& parent : parents){
			auto children = parent.first.crossOverUniform(parent.second);
			population.push_back(children.first);
			population.push_back(children.second);
		}
		for (auto& entity : population)
			entity.mutate(mutateChance);

	}
    os.close();
	popSort();
}

void Population::getPop(ostream& os){
	signed long long average = 0;
	for (auto e : population)
		average += e.getFitness();
    os << population[0].getFenotype()<< "\t" << population[0].getFitness() << endl;
    //os << (double)average / population.size() << endl;
    cout << "Average fitness is: " << (double)average / population.size() << endl;
}

void Population::popSort(){
	std::sort(population.begin(), population.end(), [](Entity e1, Entity e2){return e1.getFitness() > e2.getFitness(); });
}

vector<pair<Entity, Entity>> Population::chooseParents(){
	int prob = population.size() * 5 + 1;
	int probSum = ((1 + prob) * population.size()) / 2;
	vector<pair<Entity, Entity>> retVal;
	for (int i = 0; i < population.size() / 2; ++i)
		retVal.push_back({ population[probabilities.at(rand() % probSum)], population[probabilities.at(rand() % probSum)] }); //Relatively even distribution with %
	return retVal;
}
