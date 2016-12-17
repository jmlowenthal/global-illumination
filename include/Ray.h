#pragma once

#include "Matrix.h"

class Ray {
private:
	Vector<3> origin, direction;

public:
	Vector<3> getOrigin() { return origin; };
	Vector<3> getDirection() { return direction; };
	
	void setOrigin(Vector<3> v) { origin = v; };
	void setDirection(Vector<3> v) { direction = v; };
};
