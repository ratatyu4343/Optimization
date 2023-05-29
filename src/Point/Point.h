#ifndef POINT_POINT_H_
#define POINT_POINT_H_

#include <vector>
#include <random>
#include <time.h>

static std::mt19937 RandomGenerator(time(0));

using point = std::vector<float>;
using limit_set = std::vector<std::pair<float, float>>;

point generatePoint(int D, limit_set& limits);

std::vector<point> generatePoints(int D, int count, limit_set& limits);

void limitPoint(point& Point, limit_set& limits);

bool isAccepting(float Probability);

#endif
