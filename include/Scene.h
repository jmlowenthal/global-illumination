#pragma once

#ifndef SCENE_H
#define SCENE_H

#include "Matrix.h"
#include "Shape.h"
#include "RaycastHit.h"
#include <array>

#include <fstream>

class Scene {
private:
	int count = 0;
	std::array<Shape*, 32> shapes = {}; // nullptr array
	Vector<3> background = Vector<3>({0.9, 0.9, 0.9});

public:
	void add(Shape& s) { shapes[count++] = &s; };
	Vector<3> trace(Ray ray, int depth = 0);
	RaycastHit intersect(Ray ray);
};

#endif