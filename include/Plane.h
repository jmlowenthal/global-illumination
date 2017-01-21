#pragma once

#ifndef PLANE_H
#define PLANE_H

#include "Shape.h"

class Plane : public Shape {
private:
	Vector<3> position, normal;

public:
	Plane() : position(), normal() {};
	Plane(Vector<3> p, Vector<3> n) : position(p), normal(n) {};
	virtual RaycastHit intersect(Ray ray);
    virtual Vector<3> getNormalAt(Vector<3> pos) { return normal; };
};

#endif