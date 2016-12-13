#pragma once

#include <Matrix.h>

#define _USE_MATH_DEFINES
#include <math.h>

struct Ray {
	Vector<3> origin, direction;
	Ray() {};
	Ray(Vector<3> o, Vector<3> d) : origin(o), direction(d) {};
};

class Camera {
	int width_px, height_px;
	double aperture, length;
	double tanTheta;

	Vector<2> randInUnitDisk();

public:
	Camera(int w, int h, double a = 1.0, double l = 1.0, double fov = M_PI / 4);
	Ray cast(int x, int y);
};

#pragma region Function definitions

inline double randd() {
	return double(rand()) / RAND_MAX;
}

inline Vector<2> Camera::randInUnitDisk() {
	double phi, r;
	double a = 2 * randd() - 1;
	double b = 2 * randd() - 1;
	if (a == 0 && b == 0) a = DBL_TRUE_MIN;

	if (a * a > b * b) {
		r = a;
		phi = (M_PI / 4) * (b / a);
	}
	else {
		r = b;
		phi = (M_PI / 2) - (M_PI / 4) * (a / b);
	}

	return Vector<2>({r * cos(phi), r * sin(phi)});
}

inline Camera::Camera(int w, int h, double a, double l, double fov)
	: width_px(w), height_px(h), aperture(a), length(l) {
	tanTheta = tan(fov / 2);
}

inline Ray Camera::cast(int x, int y) {
	Ray r;

	//r.origin = randInUnitDisk().resize<3, 1>() * aperture;
	/*r.direction = Vector<3>({
		(x_step - width) / 2 + x * x_step,
		(y_step + height) / 2 - y * y_step,
		length
	});*/

	double hw = length * tanTheta;
	double hh = hw * double(height_px) / double(width_px);

	double ratio = 2 * hw / width_px;

	r.direction = Vector<3>({
		x * ratio - hw,
		-y * ratio + hh,
		-length
	});

	//r.direction += randInUnitDisk().resize<3, 1>();
	r.direction -= r.origin * ratio;
	r.direction = r.direction.normalise();

	return r;
}

#pragma endregion