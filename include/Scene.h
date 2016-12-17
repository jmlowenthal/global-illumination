#pragma once

#include "Shape.h"
#include "RaycastHit.h"

class Scene {
private:
	std::list<Shape&> shapes;

public:
	Vector<3> trace(Ray ray, int depth);
	RaycastHit intersect(Ray ray);
}
