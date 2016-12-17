#pragma once

#include "Matrix.h"
#include "Ray.h"

class Camera {
private:
	int width_px, height_px;
	double aperture;
	double focalLength;
	double tanTheta;

	Vector<2> randInUnitDisk();

public:
	Ray cast(int x, int y);
}
