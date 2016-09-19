#include <iostream>
#include "genetic.h"
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>

void main(){

	srand(time(NULL)); //Initialising rng seed

	std::string fileName; 
	std::cin >> fileName; // Specify the file name
	std::ifstream input;
	input.open(fileName);

	int capacity, mutateChance, maxGen, popSize;
	input >> capacity >> mutateChance >> maxGen >> popSize;
	std::vector<std::pair<int, int>> objects;
	int weight, value;
	for (int i = 0; i < popSize; ++i)
		input >> weight >> value, objects.push_back({ weight, value });

	Population pop{ objects, capacity, mutateChance, maxGen, popSize };
	pop.evolve(); //All the fun stuff happens here
	std::cout << std::endl;
	pop.getPop();
	for (int i = 0; i < 50; ++i) //This is just so the program doesn't close instantly
		getchar();
}