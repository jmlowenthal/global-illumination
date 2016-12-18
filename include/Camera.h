#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "Matrix.h"
#include "Ray.h"

class Camera {
private:
	double aperture;
	double focalLength;
	double tanTheta;

	Vector<2> randInUnitDisk();

public:
	Camera(double a, double fl, double theta) :
		aperture(a), focalLength(fl), tanTheta(tan(theta)) {}
	Ray cast(double x, double y);
};

#endif