#include "Renderer.h"
#include "Camera.h"
#include "utils.h"
#include <stdio.h>

Image Renderer::render(int w, int h) {
    Image img(w, h);

    double invfactor = 2.0 / std::max(w, h);
    double hw = w / 2.0, hh = h / 2.0;

    #pragma omp parallel for schedule(dynamic, 1)
    for (int x = 0; x < w; ++x) {
        fprintf(stderr, "\rRendering %5.2f%%", 100.0 * x / (w - 1));
        for (int y = 0; y < h; ++y) {
            // Trace samples
            Vector<3> c;
            for (int i = 0; i < samples; ++i) {
                Vector<2> pos({
                    (x - hw), (y - hh)
                });
                pos += randInUnitDisk();
                pos *= invfactor;

                Ray ray = camera.cast(
                    pos.at_(0), pos.at_(1)
                );

                c += scene.trace(ray);
            }
            c /= samples;

            // From Vector<3, double> -> char[3]
            img.setPixelR(x, y, clampf(c.at_(0)) * 255);
            img.setPixelG(x, y, clampf(c.at_(1)) * 255);
            img.setPixelB(x, y, clampf(c.at_(2)) * 255);
        }
    }
    printf("\n");
    return img;
}