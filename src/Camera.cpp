#include "Camera.h"
#include "utils.h"

Vector<2> randInUnitDisk() {
    double a = 2 * randd() - 1;
    double b = 2 * randd() - 1;
    if (a == 0 && b == 0) a = 1e-5;

    double r, phi;
    if (a * a > b * b) {
        r = a;
        phi = (M_PI / 4) * (b / a);
    }
    else {
        r = b;
        phi = (M_PI / 2) - (M_PI / 4) * (a / b);
    }

    return Vector<2>({
        r * cos(phi),
        r * sin(phi)
    });
}

Ray Camera::cast(double x, double y) {
    Vector<3> origin = randInUnitDisk().resize<3, 1>() * aperture;
    Vector<3> direction({
        x * focalLength * tanTheta,
        y * focalLength * tanTheta,
        -focalLength
    });
    return Ray(origin, (direction - origin).normalise());
}