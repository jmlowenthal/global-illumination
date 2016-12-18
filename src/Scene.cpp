#include "Matrix.h"
#include "Scene.h"

RaycastHit Scene::intersect(Ray ray) {
    RaycastHit result;
    for (Shape* s : shapes) {
        RaycastHit current = s->intersect(ray);
        if (current.getDistance() < result.getDistance()) {
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
    Vector<3> position = hit.getPosition();
    Vector<3> normal = shape.getNormalAt(position);

    return background;
}