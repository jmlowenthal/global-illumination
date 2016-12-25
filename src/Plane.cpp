#include "Plane.h"

RaycastHit Plane::intersect(Ray ray) {
    double Dn = ray.getDirection().dot(normal);
    if (Dn == 0) return RaycastHit();
    
    double s = (position - ray.getOrigin()).dot(normal) / Dn;
    if (s > 0) {
        return RaycastHit(*this,
            s * ray.getDirection().magnitude(),
            ray.evaluate(s)
        );
    }
    else {
        return RaycastHit();
    }
}