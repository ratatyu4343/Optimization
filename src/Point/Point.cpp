#include "Point.h"

point generatePoint(int D, limit_set& limits){
	point newPoint(D);

	for(int i = 0; i < D; i++){
		std::uniform_real_distribution<float> distribution(limits[i].first, limits[i].second);
		newPoint[i] = distribution(RandomGenerator);
	}

	return newPoint;
}

std::vector<point> generatePoints(int D, int count, limit_set& limits){
	std::vector<point> points;

	for(int i = 0; i < count; i++){
		points.push_back(generatePoint(D, limits));
	}

	return points;
}

void limitPoint(point& Point, limit_set& limits){
	for(int i = 0; i < Point.size(); i++){
		float& p = Point[i];
		if(p < limits[i].first)
			p = limits[i].first;
		else if(p > limits[i].second)
			p = limits[i].second;
	}
}

bool isAccepting(float Probability){
	std::uniform_real_distribution<float> distribution(0, 1);

	float i = distribution(RandomGenerator);

	if(i <= Probability) {
		return true;
	}

	return false;
}

float squareDifference(std::vector<float> p, std::vector<float> need_to_be) {
    float squareDiff = 0.0f;
    for (size_t i = 0; i < p.size(); ++i) {
        float diff = p[i] - need_to_be[i];
        squareDiff += diff * diff;
    }

    return squareDiff;
}

void normalize(std::vector<float>& v){
	for(float& f : v){
		f = std::log(f);
	}

	float maxx = *std::max_element(v.begin(), v.end());

	for(float& f : v){
		f /= maxx;
	}
}

