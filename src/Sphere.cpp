#include "Sphere.h"

RaycastHit Sphere::intersect(Ray ray) {
    Vector<3> rel = ray.getOrigin() - position;
    
    double a = ray.getDirection().magnitudeSq();
    double b = 2 * rel.dot(ray.getDirection());
    double c = rel.magnitudeSq() - radius * radius;
    
    double det = b * b - 4 * a * c;
    if (det < 0) return RaycastHit();

    det = sqrt(det);
    double s1 = (-b + det) / (2 * a);
    double s2 = (-b - det) / (2 * a);

    if (s1 > s2) std::swap(s1, s2);

    if (s1 < 0) {
        s1 = s2;
        if (s1 < 0) return RaycastHit();
    }

    return RaycastHit(*this,
        s1 * ray.getDirection().magnitude(),
        ray.evaluate(s1)
    );
}

Vector<3> Sphere::getNormalAt(Vector<3> pos) {
    return (pos - position).normalise();
}