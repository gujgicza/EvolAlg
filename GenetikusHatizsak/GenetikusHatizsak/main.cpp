#include <iostream>
#include "genetic.h"
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>

void main(){

	srand(time(NULL));

	std::string fileName;
	std::cin >> fileName;
	std::ifstream input;
	input.open(fileName);

	int capacity, mutateChance, maxGen, popSize;
	input >> capacity >> mutateChance >> maxGen >> popSize;
	std::vector<std::pair<int, int>> objects;
	int weight, value;
	for (int i = 0; i < popSize; ++i)
		input >> weight >> value, objects.push_back({ weight, value });
	Population pop{ objects, capacity, mutateChance, maxGen, popSize };
	pop.evolve();
	std::cout << std::endl;
	pop.getPop();
	getchar();
}