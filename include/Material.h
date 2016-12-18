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
	Vector<3> getEmission() { return emission; };
	Vector<3> getColour() { return colour; };
	ReflectiveType getType() { return type; };
};

#endif