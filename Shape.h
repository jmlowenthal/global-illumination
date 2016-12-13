#pragma once

#include "Camera.h"

enum Refl_t {
	DIFF, SPEC, REFR
};

class Shape {
protected:
	Shape(Vector<3> e, Vector<3> c, Refl_t r) : emission(e), colour(c), refl(r) {};

public:
	Vector<3> emission, colour; Refl_t refl;
	virtual double intersect(const Ray& r) const = 0; // returns distance, 0 if nohit
	virtual Vector<3> getNormalAt(const Vector<3>& v) const = 0;
};

class Sphere : public Shape {
	Vector<3> position;
	double radius;

public:
	Sphere(double rad, Vector<3> p, Vector<3> e, Vector<3> c, Refl_t refl) :
		radius(rad), position(p), Shape(e, c, refl) {};


	virtual double intersect(const Ray &ray) const {
		Vector<3> O = ray.origin;
		Vector<3> D = ray.direction.normalise();
		Vector<3> C = position;
		Vector<3> R = O - C;

		double a = D.dot(D);
		double b = 2 * D.dot(R);
		double c = R.dot(R) - (radius * radius);
		double d = b * b - 4 * a * c;

		if (d < 0) {
			return 0;
		}

		double s1 = (-b + sqrt(d)) / (2 * a);
		double s2 = (-b - sqrt(d)) / (2 * a);

		if (s1 > 0 && s2 > 0) return std::min({s1, s2}) * ray.direction.magnitude();
		else if (s1 > 0) return s1 * ray.direction.magnitude();
		else if (s2 > 0) return s2 * ray.direction.magnitude();
		else return 0;
	}

	virtual Vector<3> getNormalAt(const Vector<3>& v) const {
		return (v - position).normalise();
	}
};

class Plane : public Shape {
	Vector<3> position, normal;

public:
	Plane(Vector<3> p, Vector<3> n, Vector<3> e, Vector<3> c, Refl_t refl) :
		position(p), normal(n.normalise()), Shape(e, c, refl) {};

	virtual double intersect(const Ray & r) const {
		// (P - position).dot(normal) = 0
		// (r.origin + t * r.direction - position).dot(normal) = 0
		// (t * r.direction).dot(normal) = (position - r.origin).dot(normal)
		double t = (position - r.origin).dot(normal) / r.direction.dot(normal);
		if (t < 0) return 0;
		return t * r.direction.magnitude();
	}

	virtual Vector<3> getNormalAt(const Vector<3>& v) const {
		return normal;
	}
};