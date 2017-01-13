#include "Matrix.h"
#include "Scene.h"
#include "utils.h"

#include <string>
#include <sstream>

#define BIAS 0.0001

RaycastHit Scene::intersect(Ray ray) {
    RaycastHit result;
    for (int i = 0; i < count; ++i) {
        Shape* s = shapes[i];
        RaycastHit current = s->intersect(ray);
        if (current.getDistance() < result.getDistance() && current.getDistance() > 0) {
            result = current;
        }
    }
    return result;
}

Vector<3> Scene::trace(Ray ray, int depth) {
    RaycastHit hit = intersect(ray);
    if (!hit.hasHit()) {
        return background;
    }

    Shape& shape = *hit.getShape();
    Material material = shape.getMaterial();

    /*if (depth < 1) {
        return material.getEmission();
    }*/

    Vector<3> position = hit.getPosition();
    Vector<3> normal = shape.getNormalAt(position);
    Vector<3> normall = normal.dot(ray.getDirection()) < 0 ? normal : normal * -1;
    Vector<3> colour = material.getColour();

    // Russian Roulette
    double M = std::max(colour.at_(0), std::max(colour.at_(1), colour.at_(2)));
    if (randd() > M) {
        return material.getEmission();
    }
    else {
        colour /= M;
    }

    switch (material.getType()) {
        case DIFFUSE: {
            double r1 = 2 * M_PI * randd();
            double r2 = randd();
            double r2s = sqrt(r2);

            Vector<3> w = normall;
            Vector<3> u;
            // u = (if abs(w.x) > 0.1 then {0, 1, 0} else {1, 0, 0}) % w
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
        case SPECULAR: {
            Vector<3> direction = ray.getDirection() - normal * 2 * normal.dot(ray.getDirection());
            Ray nr(position + direction * BIAS, direction);
            return material.getEmission() + colour() * trace(nr, depth - 1);
        }
        case REFRACTIVE: {
            // SNELL'S LAW
            double c = -normall.dot(ray.getDirection()); // cos(theta_i)

            Vector<3> v_reflect = ray.getDirection() + normall * 2 * c;
            Ray ray_reflect(position + v_reflect * BIAS, v_reflect);

            bool into = normal.dot(normall) > 0;
            double n1 = 1.53;   // From     Glass
            double n2 = 1.0;    // To       Air
            if (into) std::swap(n1, n2);

            // Quick return: Total internal reflection
            if (1 - c * c > sq(n2 / n1)) {
                return material.getEmission() + colour() * trace(ray_reflect, depth - 1);
            }
            
            double r = n1 / n2;
            Vector<3> v_refract = ray.getDirection() * r + normall * (r * c - sqrt(1 - r * r * (1 - c * c)));
            Ray ray_refract(position + v_refract * BIAS, v_refract);

            // FRESHNEL EQUATIONS (Schlick's approximation)

            double R0 = sq((n1 - n2) / (n1 + n2));
            double costerm;
            if (n1 <= n2) { // R0 + (1 - R0)(1 - cos(incident))^5
                costerm = 1 - c;
            }
            else if (n1 > n2) { // R0 + (1 - R0)(1 - cos(transmitted))^5
                costerm = 1 + normall.dot(v_refract);
            }

            double R = R0 + (1 - R0) * costerm * costerm * costerm * costerm * costerm;
            double T = 1 - R;

            // Russian Roulette
            double P = 0.25 + 0.5 * R;
            if (randd() < P) {
                return material.getEmission() + colour() * trace(ray_reflect, depth - 1) / P;
            }
            else {
                return material.getEmission() + colour() * trace(ray_refract, depth - 1) / (1 - P);
            }

            return material.getEmission() + colour() * (
                trace(ray_reflect, depth - 1) * R +
                trace(ray_refract, depth - 1) * T
            );
        }
        default:
            return material.getEmission();
    }
}