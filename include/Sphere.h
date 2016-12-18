#pragma once

#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

class Sphere : public Shape {
private:
	Vector<3> position;
	double radius;

public:
	virtual RaycastHit intersect(Ray ray);
	virtual Vector<3> getNormalAt(Vector<3> pos);
};

#endif