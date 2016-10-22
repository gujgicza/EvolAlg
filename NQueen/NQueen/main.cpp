#include <iostream>
#include "genetic.h"
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>

void main(){

	srand(time(NULL)); //Initialising rng seed

	int sizeOfBoard, mutateChance, maxGen, popSize;
	std::cin >> sizeOfBoard >> mutateChance >> maxGen >> popSize;

	Population pop{sizeOfBoard, mutateChance, maxGen, popSize };
	pop.evolve(); //All the fun stuff happens here
	std::cout << std::endl;
	pop.getPop();
	for (int i = 0; i < 50; ++i) //This is just so the program doesn't close instantly
		getchar();
}