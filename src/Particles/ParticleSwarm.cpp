#include "ParticleSwarm.h"
#include <iostream>

point ParticleSwarm(int D, std::function<float(point)> ObjectiveFunction, limit_set& limits, int particleCount, int iterations, float inertW, float c1, float c2){

	point globalBestSolution;
	float globalBestFitness = std::numeric_limits<float>::max();

	std::vector<Particle> particles = generateSwarm(D, ObjectiveFunction, limits, particleCount, globalBestSolution, globalBestFitness);

	int k = 1;

	while(k <= iterations){
		for (int i = 0; i < particleCount; i++) {
			Particle& particle = particles[i];

			particle.updateVelocity(globalBestSolution, inertW, c1, c2);
			particle.updatePosition(limits);

			float fitness = ObjectiveFunction(particle.x);

			if(fitness < particle.bestFitness){
				particle.best = particle.x;
				particle.bestFitness = fitness;

				if(fitness < globalBestFitness){
					globalBestSolution = particle.x;
					globalBestFitness = fitness;
				}
			}
		}
		k++;
	}

	return globalBestSolution;
}

std::vector<Particle> generateSwarm(int D, std::function<float(point)> objFunc, limit_set& limits, int count, point& globalBest, float& globalFitness){
	std::vector<Particle> swarm(count);

	for (int i = 0; i < count; i++){
		swarm[i] = Particle::generate(D, objFunc, limits);

		if(swarm[i].bestFitness < globalFitness){
			globalFitness = swarm[i].bestFitness;
			globalBest = swarm[i].best;
		}
	}

	return swarm;
}

void Particle::updateVelocity(point& globalBest, float inertW, float c1, float c2){
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	for (int i = 0; i < x.size(); i++) {
		double r1 = distribution(RandomGenerator);
		double r2 = distribution(RandomGenerator);
		v[i] = inertW*v[i] + c1*r1*(best[i] - x[i]) + c2*r2*(globalBest[i] - x[i]);
	}
}

void Particle::updatePosition(limit_set& limits){
	for(int i = 0; i < x.size(); i++)
		x[i] += v[i];
	limitPoint(x, limits);
}

Particle Particle::generate(int D, std::function<float(point)> objFunc, limit_set& limits){
	Particle p;

	p.x.resize(D);
	p.v.resize(D);
	p.best.resize(D);

	for (int j = 0; j < D; ++j) {
		std::uniform_real_distribution<double> positionDistribution(limits[j].first, limits[j].second);
		p.x[j] = positionDistribution(RandomGenerator);
		p.v[j] = 0.0;
		p.best[j] = p.x[j];
	}

	p.bestFitness = objFunc(p.best);

	return p;
}
