#ifndef ANNEALING_ANNEALING_H_
#define ANNEALING_ANNEALING_H_

#include <vector>
#include <functional>
#include <cmath>
#include <random>
#include "../Point/Point.h"

point CauchyAnnealing(int D,
					  std::function<float(point)> ObjectiveFunction,
					  limit_set& limits,
					  float T0,
					  float Tmin,
					  int L0 = 1);

point generateNextCauchyPoint(point, float T);

float acceptanceProbability(float deltaE, float temperature);

#endif
