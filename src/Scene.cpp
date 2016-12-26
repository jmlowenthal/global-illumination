#include "Matrix.h"
#include "Scene.h"
#include "utils.h"

#include <string>
#include <sstream>

#define BIAS 0.0001

RaycastHit Scene::intersect(Ray ray) {
    RaycastHit result;
    for (Shape* s : shapes) {
        RaycastHit current = s->intersect(ray);
        if (current.getDistance() < result.getDistance() && current.getDistance() > 0) {
            result = current;
        }
    }
    return result;
}

Vector<3> Scene::trace(Ray ray, int depth) {
    if (depth < 1) {
        return background;
    }

    RaycastHit hit = intersect(ray);
    if (!hit.hasHit()) {
        return background;
    }

    Shape& shape = *hit.getShape();
    Material material = shape.getMaterial();
    Vector<3> position = hit.getPosition();
    Vector<3> normal = shape.getNormalAt(position);
    Vector<3> normall = normal.dot(ray.getDirection()) < 0 ? normal : normal * -1;
    Vector<3> colour = material.getColour();

    if (material.getType() == DIFFUSE) {
        double r1 = 2 * M_PI * randd();
        double r2 = randd();
        double r2s = sqrt(r2);

        Vector<3> w = normall;
        Vector<3> u;
        // u = (if abs(w.x) > 0.1 then {0, 1, 0} else {1, 0, 0}) % w
        /*if (w.at_(1) != 0 || w.at_(2) != 0) {
			u = Vector<3>({0, -w.at_(2), w.at_(1)});
		}
		else if (w.at_(0) != 0 || w.at_(2) != 0) {
			u = Vector<3>({-w.at_(2), 0, w.at_(0)});
		}
		else { // Hopefully not...
			u = Vector<3>({1, 0, 0});
		}*/

        if (fabs(w.at_(0)) > 0.1) {
            u = Vector<3>({0, 1, 0});
        }
        else {
            u = Vector<3>({1, 0, 0});
        }
        u = (u % w).normalise();

        Vector<3> v = w % u;

        Vector<3> direction(
            u * cos(r1) * r2s + v * sin(r1) * r2s + w * sqrt(1 - r2) 
        );
        
        direction = direction.normalise();
        Ray nr(position + direction * BIAS, direction);
        
        return material.getEmission() + colour() * trace(nr, depth - 1); 
    }
}