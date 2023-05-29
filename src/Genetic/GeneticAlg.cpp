#include "GeneticAlg.h"
#include <iostream>


point GeneticAlgorythm(int DIM, int iterations, std::function<float(point)> ObjectiveFunction, int population_size, float mutate_prob, float invers_prob, limit_set& limits){
	// Generate an initial population of points
	std::vector<point> population = generatePoints(DIM, population_size, limits);

	float best_fitness = std::numeric_limits<float>::max();
	point best_point;

	for (int iteration = 0; iteration < iterations; iteration++) {
		// intermidiate population for crossover
		std::vector<point> inter_population = intermidPopulation(population, ObjectiveFunction);

		// Perform crossover and mutation to create the next generation
		std::vector<point> next_generation;
		for (int i = 0; i < inter_population.size(); i += 2) {
			point parent1 = inter_population[i];
			point parent2 = inter_population[i + 1];

			// Apply crossover to produce offspring
			std::pair<point, point> offspring = crossing(parent1, parent2);

			// Apply mutation to each offspring
			point mutated_offspring1 = mutation(offspring.first, mutate_prob, limits);
			point mutated_offspring2 = mutation(offspring.second, mutate_prob, limits);

			// Apply inversion to each offspring
			point inverted_offspring1 = inversion(mutated_offspring1, invers_prob);
			point inverted_offspring2 = inversion(mutated_offspring2, invers_prob);

			// Limit the offspring points to the defined limits
			limitPoint(inverted_offspring1, limits);
			limitPoint(inverted_offspring2, limits);

			// Add the offspring to the next generation
			next_generation.push_back(inverted_offspring1);
			next_generation.push_back(inverted_offspring2);
		}

		// Find the best point
		for (const auto& individual : population) {
			float fitness = ObjectiveFunction(individual);

			if (fitness < best_fitness) {
				best_fitness = fitness;
				best_point = individual;
			}
		}

		// Update the population with the new generation
		population = std::move(next_generation);
	}

	return best_point;
}

std::pair<point, point> crossing(point& p1, point& p2) {
    std::uniform_int_distribution<int> distribution(0, p1.size() - 1);

    // Generate random index for crossover point
    int idx = distribution(RandomGenerator);

    point p_child_1, p_child_2;

    // Copy elements up to the crossover point
    p_child_1.insert(p_child_1.end(), p1.begin(), p1.begin() + idx + 1);
    p_child_2.insert(p_child_2.end(), p2.begin(), p2.begin() + idx + 1);

    // Copy remaining elements from the crossover point
    p_child_1.insert(p_child_1.end(), p2.begin() + idx + 1, p2.end());
    p_child_2.insert(p_child_2.end(), p1.begin() + idx + 1, p1.end());

    return std::make_pair(p_child_1, p_child_2);
}

point mutation(point p, float Prob,  limit_set& limits){
	point newPoint = generatePoint(p.size(), limits);

	for(int i = 0; i < p.size(); i++){
		if(isAccepting(Prob)){
			p[i] = newPoint[i];
		}
	}

	return p;
}

point inversion(point p, float Prob){
	if(isAccepting(Prob)){
		std::uniform_int_distribution<int> destribution(0, p.size()-1);
		int x1 = destribution(RandomGenerator);
		int x2 = destribution(RandomGenerator);

		auto start_inversion = p.begin() + std::min(x1, x2);
		auto end_inversion = p.begin() + std::max(x1, x2) + 1;

		std::reverse(start_inversion, end_inversion);
	}

	return p;
}

std::vector<point> intermidPopulation(std::vector<point>& population, std::function<float(point)> ObjectiveFunction){
	// Evaluate fitness for each point in the population
	std::vector<float> fitness_values;

	for (const auto& individual : population) {
		// Calculate fitness value for the individual and store it
		float fitness = ObjectiveFunction(individual);
		fitness_values.push_back(fitness);
	}

	// tournament selection
	std::vector<point> intermediate_population;
	int population_size = population.size();
	int tournament_size = 2;
	std::uniform_int_distribution<int> distribution(0, population_size-1);

	for (int i = 0; i < population_size; i++) {
		// Randomly choose two individuals for the tournament
		int candidate1 = distribution(RandomGenerator);
		int candidate2 = distribution(RandomGenerator);

		// tournament between the two candidates
		int selected_individual = tournamentSelection(population, fitness_values, candidate1, candidate2);

		// Add the selected individual to the intermediate population
		intermediate_population.push_back(population[selected_individual]);
	}

	return intermediate_population;
}

int tournamentSelection(std::vector<point>& population, std::vector<float>& fitness_values, int candidate1, int candidate2) {
    // Get fitness values of the two candidates
    float fitness1 = fitness_values[candidate1];
    float fitness2 = fitness_values[candidate2];

    // Choose the fitter candidate based on their fitness values
    if (fitness1 >= fitness2) {
        return candidate1;
    } else {
        return candidate2;
    }
}








