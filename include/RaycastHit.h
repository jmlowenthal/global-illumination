#pragma once

#ifndef RAYCASTHIT_H
#define RAYCASTHIT_H

#include <limits>
#include "Matrix.h"

#define DBL_MAX std::numeric_limits<double>::max()

class RaycastHit;
#include "Shape.h"

class RaycastHit {
private:
	double distance;
	Vector<3> position;
	Shape* shape;

public:
	RaycastHit() : distance(DBL_MAX) {}
	RaycastHit(Shape& s) : shape(&s), distance(DBL_MAX) {}
	RaycastHit(Shape& s, double d, Vector<3> p) : shape(&s), distance(d), position(p) {};

	double getDistance() { return distance; };
	Vector<3> getPosition() { return position; };
	Shape* getShape() { return shape; };
	bool hasHit() { return distance < std::numeric_limits<double>::max(); };
};

#endif