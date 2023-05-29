#ifndef PARTICLES_PARTICLESWARM_H_
#define PARTICLES_PARTICLESWARM_H_

#include <functional>
#include <vector>
#include <random>
#include <limits>
#include "../Point/Point.h"

struct Particle{
	point x;
	point v;
	point best;
	float bestFitness;

	void updatePosition(limit_set& limits);
	void updateVelocity(point& globalBest, float inertW, float c1, float c2);
	static Particle generate(int D, std::function<float(point)> objFunc, limit_set& limits);
};

point ParticleSwarm(int D,
					std::function<float(point)> ObjectiveFunction,
					limit_set& limits,
					int particleCount, int iterations,
					float inertW, float c1, float c2);

std::vector<Particle> generateSwarm(int D,
									std::function<float(point)> objFunc,
									limit_set& limits,
									int count, point& globalBest,
									float& globalFitness);

#endif
