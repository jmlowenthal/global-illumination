#include "Sphere.h"

RaycastHit Sphere::intersect(Ray ray) {
    return RaycastHit(*this);
}

Vector<3> Sphere::getNormalAt(Vector<3> pos) {
    return (pos - position).normalise();
}