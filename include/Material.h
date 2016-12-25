#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Matrix.h"

enum ReflectiveType {
	DIFFUSE, SPECULAR, REFRACTIVE
};

class Material {
private:
	Vector<3> emission, colour;
	ReflectiveType type;

public:
	Material() {};
	Material(Vector<3> e, Vector<3> c, ReflectiveType t) : emission(e), colour(c), type(t) {};
	Vector<3> getEmission() { return emission; };
	Vector<3> getColour() { return colour; };
	ReflectiveType getType() { return type; };
};

#endif