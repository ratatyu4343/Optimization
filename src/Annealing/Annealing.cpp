#include "Annealing.h"
#include <iostream>

point CauchyAnnealing(int D, std::function<float(point)> ObjectiveFunction,  limit_set& limits, float T0, float T_min, int L0){
	float T_current = T0;

	point Point_current = generatePoint(D, limits);
	limitPoint(Point_current, limits);

	point Point_best = Point_current;
	float Energy_best = ObjectiveFunction(Point_best);

	int k = 1;

	while(T_current > T_min){

		for (int i = 0; i < L0; i++){
			point Point_next = generateNextCauchyPoint(Point_current, T_current);
			limitPoint(Point_next, limits);

			float Energy_curr = ObjectiveFunction(Point_current);
			float Energy_next = ObjectiveFunction(Point_next);
			float Energy_diff = Energy_next - Energy_curr;

			float acceptProb = acceptanceProbability(Energy_diff, T_current);

			if(isAccepting(acceptProb))
				Point_current = Point_next;

			if(Energy_next < Energy_best){
				Energy_best = Energy_next;
				Point_best = Point_next;
			}

		}

		T_current = T0 / k;
		k++;
	}

	return Point_best;
}

//need to be changed!!!!!!!!!!!!!
point generateNextCauchyPoint(point p, float T){
	for(int i = 0; i < p.size(); i++){
		std::cauchy_distribution<float> distribution(p[i], T);
		p[i] = distribution(RandomGenerator);
	}
	return p;
}

float acceptanceProbability(float deltaE, float temperature) {
    if (deltaE < 0) {
        return 1.0;
    } else {
    	return std::exp(-deltaE / temperature);
    }
}
