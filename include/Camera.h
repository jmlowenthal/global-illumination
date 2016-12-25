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

public:
	Camera(double a, double fl, double fov) :
		aperture(a), focalLength(fl), tanTheta(tan(fov / 2)) {}
	Ray cast(double x, double y);
};

Vector<3> randInUnitDisk();

#endif