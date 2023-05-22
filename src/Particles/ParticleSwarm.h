#ifndef PARTICLES_PARTICLESWARM_H_
#define PARTICLES_PARTICLESWARM_H_

#include <functional>
#include <vector>
#include <random>
#include <limits>
#include <time.h>

using point = std::vector<float>;

struct Particle{
	point x;
	point v;
	point best;
	float bestFitness;

	void updatePosition(std::vector<std::pair<float, float>>& limits);
	void updateVelocity(point& globalBest, float inertW, float c1, float c2);
	static Particle generate(int D, std::function<float(point)> objFunc, std::vector<std::pair<float, float>>& limits);
};

point ParticleSwarm(int D,
					std::function<float(point)> ObjectiveFunction,
					std::vector<std::pair<float, float>>& limits,
					int particleCount, int iterations,
					float inertW, float c1, float c2);

std::vector<Particle> generateSwarm(int D,
									std::function<float(point)> objFunc,
									std::vector<std::pair<float, float>>& limits,
									int count, point& globalBest,
									float& globalFitness);

void limitPoint(point& Point, std::vector<std::pair<float, float>> limits);

#endif
