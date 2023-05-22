#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>
#include "Annealing/Annealing.h"
#include "Particles/ParticleSwarm.h"


float objFunction(const std::vector<float>& p) {
    // Example test function: Styblinski-Tang function
    float sum = 0.0f;
    for (float x : p) {
        sum += pow(x, 4) - 16.0f * pow(x, 2) + 5.0f * x;
    }
    return 0.5f * sum;
}


float squareDifference(std::vector<float> p, std::vector<float> need_to_be) {
    float squareDiff = 0.0f;
    for (size_t i = 0; i < p.size(); ++i) {
        float diff = p[i] - need_to_be[i];
        squareDiff += diff * diff;
    }

    return std::sqrt(squareDiff);
}

int main() {
	srand(time(0));
	std::vector<std::pair<float, float>> limits = {{-5, 5}, {-5, 5}, {-5, 5}, {-5, 5}, {-5, 5}, {-5, 5}};
	std::vector<float> need_to_be = {-2.903534, -2.903534, -2.903534, -2.903534, -2.903534, -2.903534};
	int DIM = 6;

	std::vector<float> p1 = ParticleSwarm(DIM, objFunction, limits, 100, 10000, 0.95, 1, 0.8);

	for(float p : p1)
		std::cout << p << " ";
	std::cout << "\n" << squareDifference(p1, need_to_be) << std::endl;

	std::vector<float> p2 = CauchyAnnealing(DIM, objFunction, limits, 7000, 0.0005, 5);

	for(float p : p2)
		std::cout << p << " ";
	std::cout << "\n" << squareDifference(p2, need_to_be) << std::endl;

}
