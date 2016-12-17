#pragma once

#include "Shape.h"

class Plane : public Shape {
private:
	Vector<3> position, normal;

public:
	virtual RaycastHit intersect(Ray ray);
	virtual Vector<3> getNormalAt(Vector<3> pos);
}
