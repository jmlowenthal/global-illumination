#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <random>
#include <vector>

#include <Matrix.h>

#include "Camera.h"
#include "Shape.h"

#include <SDL.h>

#define BIAS 0.0001

std::vector<Shape*> scene = {
	//new Sphere(1e5, Vector<3>({0, -1e5 - 2, 0}), Vector<3>(), Vector<3>({0.3, 0.1, 0.7}), DIFF),
	new Plane(
		Vector<3>({0, -2, 0}),
		Vector<3>({0, 1, 0}),
		Vector<3>({0.5, 0.5, 0.5}),
		Vector<3>({0.4, 0.4, 0.4}),
		DIFF
	),
	/*new Sphere(1,
		Vector<3>({2, -10, 17}),
		Vector<3>({252, 212, 64}) / 255 * 100,
		Vector<3>(),
		DIFF
	),*/ // THE F*CKING SUN
};

inline bool intersect(const Ray &r, double &t, int &id) {
	int n = scene.size();
	double inf = t = DBL_MAX;

	for (int i = 0; i < n; ++i) {
		double d = scene[i]->intersect(r);
		if (d > 0 && d < t) {
			t = d; id = i;
		}
	}

	return t < inf;
}

#undef max

inline Vector<3> trace(const Ray &r, int depthLeft) {
	if (depthLeft < 1) return Vector<3>();

	double t;
	int id = 0;
	if (!intersect(r, t, id)) return Vector<3>();

	Shape * obj = scene[id];
	Vector<3> position = r.origin + r.direction * t;
	Vector<3> normal = obj->getNormalAt(position);
	Vector<3> normall = normal.dot(r.direction) < 0 ? normal : normal * -1;
	Vector<3> colour = obj->colour;

	//return obj.emission;

	/*double p = std::max({colour.at_(0), colour.at_(1), colour.at_(2)});
	if (depthLeft < 5 || !p) {
		if (randd() < p) {
			colour /= p;
		}
		else {
			return obj.emission;
		}
	}*/

	if (obj->refl == DIFF) {
		double r1 = 2 * M_PI * randd();
		double r2 = randd();
		double r2s = sqrt(r2);

		Vector<3> w = normall;
		Vector<3> u;
		if (w.at_(1) != 0 || w.at_(2) != 0) {
			u = Vector<3>({0, -w.at_(2), w.at_(1)});
		}
		else if (w.at_(0) != 0 || w.at_(2) != 0) {
			u = Vector<3>({-w.at_(2), 0, w.at_(0)});
		}
		else { // Hopefully not...
			u = Vector<3>({1, 0, 0});
		}
		u = u.normalise();

		Vector<3> v = w % u;

		Ray nr;
		nr.direction = (u * cos(r1) * r2s + v * sin(r1) * r2s + w * sqrt(1 - r2)).normalise();
		nr.origin = position + nr.direction * BIAS;

		return obj->emission + colour() * trace(nr, depthLeft - 1);
	}
	else if (obj->refl == SPEC) {
		Ray nr;
		nr.direction = r.direction - normal * 2 * normal.dot(r.direction);
		nr.origin = position + nr.direction * BIAS;

		return obj->emission + colour() * trace(nr, depthLeft - 1);
	}
	else {
		Ray nr;
		nr.direction = r.direction - normal * 2 * normal.dot(r.direction);
		nr.origin = position + nr.direction * BIAS;

		bool into = normal.dot(normall) > 0;
		double nc = 1.0, nt = 1.5, nnt = into ? nc / nt : nt / nc;
		double ddn = r.direction.dot(normall);

		double cos2t = 1 - nnt * nnt * (1 - ddn * ddn);
		if (cos2t < 0) { // total internal reflection
			return obj->emission + colour() * trace(nr, depthLeft - 1);
		}
		else {
			Vector<3> tdir = r.direction * nnt;
			tdir -= normal * ((into ? 1 : -1) * ddn * nnt + sqrt(cos2t));
			tdir = tdir.normalise();

			double a = nt - nc, b = nt + nc, c = 1 - (into ? -ddn : tdir.dot(normal));
			double R0 = a * a / (b * b);
			double Re = R0 + (1 - R0) * c * c * c * c * c;
			double Tr = 1 - Re;
			double P = 0.25 + 0.5 * Re;
			double RP = Re / P, TP = Tr / (1 - P);

			Vector<3> traced;
			if (depthLeft < 5) {
				if (randd() < P) {
					traced = trace(nr, depthLeft - 1) * RP;
				}
				else {
					nr.direction = tdir;
					traced = trace(nr, depthLeft - 1) * TP;
				}
			}
			else {
				traced = trace(nr, depthLeft - 1) * Re;
				nr.direction = tdir;
				traced += trace(nr, depthLeft - 1) * Tr;
			}

			return obj->emission + colour() * traced;
		}
	}
}

inline double clamp(double x) {
	return x < 0 ? 0 : x > 1 ? 1 : x;
}

inline int toInt(double x) {
	return clamp(x) * 255;
	//return int(pow(clamp(x), 1 / 2.2) * 255 + .5);
}

int main(int argc, char *argv[]) {
	for (int i = 0; i < 10; ++i) {
		Sphere * s = new Sphere(
			0.7,
			Vector<3>({2, 1, 2.0 + 10.0 * i}),
			Vector<3>(),
			Vector<3>({0.1, 0.4, 0}),
			DIFF
		);
		scene.push_back(s);
	}

	int w = 1000, h = 600;
	double aperture = 0.1, length = 12;
	int samples = 128;
	int bounces = 4;

	// First arg is always executable name
	if (argc % 2 != 1) return -1;
	for (int i = 1; i < argc; i += 2) {
		if (argv[i][0] != '-') return 10 - i;
		switch (argv[i][1]) {
			case 'w':
				w = atoi(argv[i + 1]);
				break;
			case 'h':
				h = atoi(argv[i + 1]);
				break;
			case 'a':
				aperture = atof(argv[i + 1]);
				break;
			case 'l':
				length = atof(argv[i + 1]);
				break;
			case 's':
				samples = atoi(argv[i + 1]);
				break;
			case 'b':
				bounces = atoi(argv[i + 1]);
				break;
		}
	}

	Camera camera(w, h, aperture, length);

	Vector<3> * c = new Vector<3>[w * h];

	SDL_Window * window = SDL_CreateWindow(
		"Render", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		w, h, NULL
	);
	if (window == nullptr) return -100;

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, NULL);
	if (renderer == nullptr) return -101;

	for (int s = 0;/* s < samples*/; ++s) {

		for (int y = 0; y < h; ++y) {
			printf("\rRenderering: %5.2f%%", 100.0 * y / (h - 1));
			for (int x = 0; x < w; ++x) {
				/*Vector<3> r;
				for (int s = 0; s < samples; ++s) {
					r += trace(camera.cast(x, y), bounces);
				}
				r /= samples;

				c[y * w + x] = Vector<3>({
					clamp(r.at_(0)), clamp(r.at_(1)), clamp(r.at_(2))
				});*/

				Vector<3> r = trace(camera.cast(x, y), bounces);

				int i = y * w + x;
				c[i] = ((c[i] * s) + r) / (s + 1);

				SDL_SetRenderDrawColor(renderer,
					toInt(c[i].at_(0)),
					toInt(c[i].at_(1)),
					toInt(c[i].at_(2)),
					0
				);
				SDL_RenderDrawPoint(renderer, x, y);
			}
		}

		SDL_RenderPresent(renderer);
	}

	while (true) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) break;
		}
	}

	/*std::ofstream f("image.ppm");
	f << "P3\n" << w << " " << h << "\n255\n";
	for (int i = 0; i < w * h; ++i) {
	f << toInt(c[i].at_(0)) << " "
	<< toInt(c[i].at_(1)) << " "
	<< toInt(c[i].at_(2)) << " ";
	}*/
}