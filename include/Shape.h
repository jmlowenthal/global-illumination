#pragma once

#ifndef SHAPE_H
#define SHAPE_H

#include "Matrix.h"
#include "Material.h"
#include "Ray.h"

class Shape;
#include "RaycastHit.h"

class Shape {
private:
	Material m;

public:
	Material getMaterial() { return m; };
	void setMaterial(Material mat) { m = mat; };

	virtual RaycastHit intersect(Ray ray) = 0;
	virtual Vector<3> getNormalAt(Vector<3> pos) = 0;
};

#endif