#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <algorithm>

std::vector<int> randomPermutation(int n){
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
	return permutations;
}

int numberOfCycles(std::vector<int> firstParent, std::vector<int> secondParent){
	std::vector<int> cycles;
	for (int i : firstParent)
		cycles.push_back(-1);
	int numOfCycles = 0;
	for (int i = 0; i < firstParent.size(); ++i){
		if (cycles[i] == -1){
			cycles[i] = numOfCycles;
			int j = i;
			while (cycles[j] != -1){
				j = std::distance(secondParent.begin(), std::find(secondParent.begin(), secondParent.end(), firstParent[j]));
				if (cycles[j] == -1)
					cycles[j] = numOfCycles;
				else
					break;
			}
			numOfCycles++;
		}
	}
/*	for (auto i : cycles)
		std::cout << i << " ";*/
	int max = 0;
	for (auto i : cycles)
		if (i > max)
			max = i;
	return max;
}

int main(){
	srand(time(NULL));
/*	std::vector<int> p1 = randomPermutation(9), p2 = randomPermutation(9);
	for (auto i : p1)
		std::cout << i << " ";
	std::cout << std::endl;
	for (auto i : p2)
		std::cout << i << " ";
	std::cout << std::endl;
	numberOfCycles(p1, p2);
	getchar();*/

	std::vector<int> results;
	for (int i = 0; i < 9; ++i)
		results.push_back(0);
	std::vector<std::pair<std::vector<int>, std::vector<int>>> parents;
	for (int i = 0; i < 100000; ++i)
		parents.push_back({ randomPermutation(9), randomPermutation(9) });

	for (auto& i : parents)
		results[numberOfCycles(i.first, i.second)]++;
	for (int i : results)
		std::cout << i << " ";
	getchar();
}