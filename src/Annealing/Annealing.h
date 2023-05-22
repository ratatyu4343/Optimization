#ifndef ANNEALING_ANNEALING_H_
#define ANNEALING_ANNEALING_H_

#include <vector>
#include <functional>
#include <cmath>
#include <random>
#include <time.h>

using point = std::vector<float>;

point CauchyAnnealing(int D,
					  std::function<float(point)> ObjectiveFunction,
					  std::vector<std::pair<float, float>> limits,
					  float T0, float Tmin, int L0 = 1);

point generateNextCauchyPoint(point, float T);

point generatePoint(int D);

float acceptanceProbability(float deltaE, float temperature);

bool isAccepting(float Probability);

void limitPoint(point& p, std::vector<std::pair<float, float>>& limits);

#endif
