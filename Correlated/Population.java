import java.util.ArrayList;
import java.util.TreeMap;

public class Population {
	AlmostLambda function;
	ArrayList<Entity> population;
	int maxGen;
	int currentGen;
	int probSum;
	int popSize;
	TreeMap<Integer, Integer> probabilities;
	
	public Population(AlmostLambda func){
		function = func;
		maxGen = 1500;
		currentGen = 0;
		popSize = 50;
		population = new ArrayList<Entity>();
		for(int i = 0; i < popSize; i++)
			population.add(new Entity(function));
		probabilities = new TreeMap<Integer, Integer>();
		int prob = popSize * 5 + 1; //First place gets e.g. 101, second gets 86 and so on.
		probSum = ((1 + prob) * popSize) / 2;
		for (int i = 0; i < population.size(); ++i){ //Places the probabilities for each ordinal number in the map
			for (int j = probSum; j > probSum - prob; --j)
				probabilities.put(j, i);
			probSum -= prob;
			prob -= 5;
		}
	}
	
	public void popSort(){
		population.sort(null);
	}
	
	public ArrayList<ArrayList<Entity>> chooseParents(){
		ArrayList<ArrayList<Entity>> retVal = new ArrayList<ArrayList<Entity>>();
		for (int i = 0; i < population.size() * 5; ++i){
			ArrayList<Entity> onePair = new ArrayList<Entity>();
			onePair.add(population.get((int) (Math.rint(Math.random() * 500) % probSum)));
			onePair.add(population.get((int) (Math.rint(Math.random() * 500) % probSum)));
			retVal.add(onePair);
		}
			//retVal.push_back({ population[probabilities.at(rand() % probSum)], population[probabilities.at(rand() % probSum)] }); //Relatively even distribution with %
		return retVal;
	}
	
	public void evolve(){
		ArrayList<Entity> tempPopulation = new ArrayList<Entity>();
		for (; currentGen < maxGen; ++currentGen){
			popSort();
			ArrayList<ArrayList<Entity>> parents = chooseParents();
			population.clear();
			ArrayList<Entity> parent;
			for (int i = 0; i < parents.size(); i++){
				parent = parents.get(i);
				ArrayList<Entity> children = parent.get(0).crossOver(parent.get(1));
				children.get(0).mutate();
				children.get(1).mutate();
				tempPopulation.add(children.get(0));
				tempPopulation.add(children.get(1));
			}
		}
		tempPopulation.sort(null);
		for(int i = 0; i < popSize; i++)
			population.add(tempPopulation.get(i));
		popSort();
	}

}
