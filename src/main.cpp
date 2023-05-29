#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>
#include "Annealing/Annealing.h"
#include "Particles/ParticleSwarm.h"
#include "Genetic/GeneticAlg.h"
#include "matplot/matplot.h"

float objFunction(const std::vector<float>& p) {
    // Example test function: Styblinski-Tang function
    float sum = 0.0f;
    for (float x : p) {
    	x -= 2.903534;
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

std::vector<double> linspace1(double start, double end, int numPoints) {
    std::vector<double> result;
    double step = (end - start) / (numPoints - 1);
    for (int i = 0; i < numPoints; ++i) {
        result.push_back(start + i * step);
    }
    return result;
}

std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>>
meshgrid2(const std::vector<double>& x, const std::vector<double>& y) {
    std::vector<std::vector<double>> X(x.size(), std::vector<double>(y.size()));
    std::vector<std::vector<double>> Y(x.size(), std::vector<double>(y.size()));
    for (size_t i = 0; i < x.size(); ++i) {
        for (size_t j = 0; j < y.size(); ++j) {
            X[i][j] = x[i];
            Y[i][j] = y[j];
        }
    }
    return std::make_pair(X, Y);
}

int main() {
	using namespace matplot;

	auto [X, Y] = meshgrid2(linspace1(-5, +5, 40), linspace1(-5, +5, 40));
	auto Z = transform(X, Y, [](double x, double y) {
	        return 10 * 2 + pow(x, 2) - 10 * cos(2 * pi * x) + pow(y, 2) - 10 * cos(2 * pi * y);});
	surf(X, Y, Z);
	show();

	std::vector<std::pair<float, float>> limits = {{-5000, 5000}, {-5000, 5000}, {-5000, 5000}, {-5, 5}, {-5, 5}, {-5, 5}, {-5, 5}, {-5, 5}, {-5, 5}, {-5, 5}};
	std::vector<float> need_to_be(5, 0);
	int DIM = 2;


	std::vector<float> p1 = ParticleSwarm(DIM, objFunction, limits, 1000, 1000, 0.95, 1, 0.95);

	for(float p : p1)
		std::cout << p << " ";
	std::cout << "\n" << squareDifference(p1, need_to_be) << std::endl;

	std::vector<float> p2 = CauchyAnnealing(DIM, objFunction, limits, 7000, 0.01, 1);

	for(float p : p2)
		std::cout << p << " ";
	std::cout << "\n" << squareDifference(p2, need_to_be) << std::endl;

	std::vector<float> p0 = GeneticAlgorythm(DIM, 1000, objFunction, 50, 0.5, 0.4, limits);

		for(float p : p0)
			std::cout << p << " ";
		std::cout << "\n" << squareDifference(p0, need_to_be) << std::endl;

}
