#pragma once

#include "Matrix.h"

class RaycastHit;
#include "Shape.h"

class RaycastHit {
private:
	double distance;
	Vector<3> position;
	Shape& shape;

public:
	double getDistance() { return distance; };
	Vector<3> getPosition() { return position; };
	Shape& getShape() { return shape; };
};
