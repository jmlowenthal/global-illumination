#include "Renderer.h"

double clampf(double v) {
    return v > 1.0 ? 1.0 : v < 0.0 ? 0.0 : v;
}

Image Renderer::render(int w, int h) {
    Image img(w, h);
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            // Trace samples
            Vector<3> c;
            for (int i = 0; i < samples; ++i) {
                c += scene.trace(camera.cast(x, y), depth);
            }
            c /= samples;

            // From Vector<3, double> -> char[3]
            img.setPixelR(x, y, clampf(c.at_(0)) * 255);
            img.setPixelG(x, y, clampf(c.at_(1)) * 255);
            img.setPixelB(x, y, clampf(c.at_(2)) * 255);
        }
    }
    return img;
}