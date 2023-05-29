#ifndef GENETIC_GENETICALG_H_
#define GENETIC_GENETICALG_H_

#include <vector>
#include <random>
#include <algorithm>
#include <functional>
#include "../Point/Point.h"

point GeneticAlgorythm(int DIM, int iterations, std::function<float(point)> ObjectiveFunction,
						int population_size, float mutate_prob, float invers_prob,
						limit_set& limits);

point mutation(point p, float Prob,  limit_set& limits);

point inversion(point p, float Prob);

std::pair<point, point> crossing(point& p1, point& p2);



std::vector<point> intermidPopulation(std::vector<point>& population, std::function<float(point)> ObjectiveFunction);

int tournamentSelection(std::vector<point>& population, std::vector<float>& fitness_values, int candidate1, int candidate2);

#endif
