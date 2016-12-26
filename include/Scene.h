#pragma once

#ifndef SCENE_H
#define SCENE_H

#include "Matrix.h"
#include "Shape.h"
#include "RaycastHit.h"
#include <vector>

#include <fstream>

class Scene {
private:
	std::vector<Shape*> shapes;
	Vector<3> background = Vector<3>();

public:
	void add(Shape& s) { shapes.push_back(&s); };
	Vector<3> trace(Ray ray, int depth);
	RaycastHit intersect(Ray ray);
};

#endif