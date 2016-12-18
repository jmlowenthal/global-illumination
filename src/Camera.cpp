#include "Camera.h"

Ray Camera::cast(double x, double y) {
    // Orthogonal
    return Ray(
        Vector<3>({x * 100, y * 100, 0}), 
        Vector<3>({0, 0, -1})
    );
}