#pragma once

#ifndef RAY_H
#define RAY_H

#include "Matrix.h"

class Ray {
private:
	Vector<3> origin, direction;

public:
	Ray() {};
	Ray(Vector<3> o, Vector<3> d) : origin(o), direction(d) {};

	Vector<3> getOrigin() { return origin; };
	Vector<3> getDirection() { return direction; };
	
	void setOrigin(Vector<3> v) { origin = v; };
	void setDirection(Vector<3> v) { direction = v; };

	Vector<3> evalute(double parameter) {
		return origin + direction * parameter;
	}
};

#endif