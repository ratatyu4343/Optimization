#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>
#include "Annealing/Annealing.h"
#include "Particles/ParticleSwarm.h"
#include "Genetic/GeneticAlg.h"
#include "plotLib/matplotlib.h"

namespace plt = matplotlibcpp;

//egg holder function
float objFunction(const std::vector<float>& p) {
	using namespace std;

    float x = p[0];
    float y = p[1];

    float term1 = -(y + 47) * sin(sqrt(fabs(x / 2 + (y + 47))));
    float term2 = -x * sin(sqrt(fabs(x - (y + 47))));

    return term1 + term2;
}

int main() {
	limit_set limits = {{-512, 512},{-512, 512}};
	std::vector<float> global_minimum{512, 404.2319};

	std::vector<float> X;
	std::vector<float> Y;

	//genetic algorythm iterations
	for(int i = 100; i <= 1000; i += 100) {
		X.push_back(i);

		float kvadrat;
		for (int j = 0; j < 100; j++){
			point ans = GeneticAlgorythm(2, i, objFunction, 20, 0.4, 0.1, limits);
			kvadrat += squareDifference(ans, global_minimum);
		}
		kvadrat /= 100;
		Y.push_back(kvadrat);
	}
	normalize(Y);
	plt::plot(X, Y, "o-");
	plt::xlabel("Кількість ітерацій");
	plt::ylabel("Середнє значення різниці квадратів");
	std::cout << "Plot 1 ready..." << std::endl;

	X.resize(0);
	Y.resize(0);
	plt::figure();

	//genetic algorythm mutations
	for(float m = 0; m <= 1; m += 0.1) {
		X.push_back(m);

		float kvadrat;
		for (int j = 0; j < 100; j++){
			point ans = GeneticAlgorythm(2, 400, objFunction, 20, m, 0.1, limits);
			kvadrat += squareDifference(ans, global_minimum);
		}
		kvadrat /= 100;
		Y.push_back(kvadrat);
	}
	normalize(Y);
	plt::plot(X, Y,  "o-");
	plt::xlabel("Ймовірність мутації");
	plt::ylabel("Середнє значення різниці квадратів");
	std::cout << "Plot 2 ready..." << std::endl;

	X.resize(0);
	Y.resize(0);
	plt::figure();

	//genetic algorythm population size
	for(int p = 10; p <= 220; p += 30) {
		X.push_back(p);

		float kvadrat;
		for (int j = 0; j < 100; j++){
			point ans = GeneticAlgorythm(2, 400, objFunction, p, 0.4, 0.1, limits);
			kvadrat += squareDifference(ans, global_minimum);
		}
		kvadrat /= 100;
		Y.push_back(kvadrat);
	}
	normalize(Y);
	plt::plot(X, Y, "o-");
	plt::xlabel("Розмір популяції");
	plt::ylabel("Середнє значення різниці квадратів");
	std::cout << "Plot 3 ready..." << std::endl;

	X.resize(0);
	Y.resize(0);
	plt::figure();

	//genetic algorythm testing
	for (int j = 0; j < 100; j++){
		point ans = GeneticAlgorythm(2, 1500, objFunction, 50, 0.5, 0.1, limits);
		X.push_back(ans[0]);
		Y.push_back(ans[1]);
	}
	plt::plot(X, Y, "o");
	plt::xlabel("x1");
	plt::ylabel("x2");
	plt::xlim(480, 540);
	plt::ylim(370, 480);
	plt::plot({global_minimum[0]},{global_minimum[1]},"ro");

	std::cout << "Plot 4 ready..." << std::endl;


	//particle swarm iterations
	for(int i = 100; i <= 3000; i += 100) {
		X.push_back(i);

		float kvadrat;
		for (int j = 0; j < 100; j++){
			point ans = ParticleSwarm(2, objFunction, limits, 100, i, 0.9, 1, 1);
			kvadrat += squareDifference(ans, global_minimum);
		}
		kvadrat /= 100;
		Y.push_back(kvadrat);
	}
	normalize(Y);
	plt::plot(X, Y, "o-");
	plt::xlabel("Кількість ітерацій");
	plt::ylabel("Середнє значення різниці квадратів");
	std::cout << "Plot 5 ready..." << std::endl;

	X.resize(0);
	Y.resize(0);
	plt::figure();

	//particle swarm count
	for(float m = 100; m <= 1000; m += 100) {
		X.push_back(m);

		float kvadrat;
		for (int j = 0; j < 100; j++){
			point ans = ParticleSwarm(2, objFunction, limits, m, 1000, 0.9, 1, 1);
			kvadrat += squareDifference(ans, global_minimum);
		}
		kvadrat /= 100;
		Y.push_back(kvadrat);
	}
	normalize(Y);
	plt::plot(X, Y,  "o-");
	plt::xlabel("Кількість частинок");
	plt::ylabel("Середнє значення різниці квадратів");
	std::cout << "Plot 6 ready..." << std::endl;

	X.resize(0);
	Y.resize(0);

	//particle swarm testing
	for (int j = 0; j < 100; j++){
		point ans = ParticleSwarm(2, objFunction, limits, 200, 1250, 0.9, 1.5, 1);
		X.push_back(ans[0]);
		Y.push_back(ans[1]);
	}
	plt::plot(X, Y, "o");
	plt::xlabel("x1");
	plt::ylabel("x2");
	plt::xlim(-1000, 1000);
	plt::ylim(-1000, 1000);
	plt::plot({global_minimum[0]},{global_minimum[1]},"ro");
	plt::figure();

	std::cout << "Plot 7 ready..." << std::endl;

	//annealing testing
	for(int i = 0; i < 100; i++) {
		point ans = CauchyAnnealing(2, objFunction, limits, 10000, 0.005, 1);
		X.push_back(ans[0]);
		Y.push_back(ans[1]);
		std::cout << i << std::endl;
	}

	plt::plot(X, Y, "o");
	plt::xlabel("x1");
	plt::ylabel("x2");
	plt::plot({global_minimum[0]},{global_minimum[1]},"ro");
	plt::xlim(-600, 600);
	plt::ylim(-600, 600);

	std::cout << "Plot 8 ready..." << std::endl;

	plt::show();
}
