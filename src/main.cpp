#include "Scene.h"
#include "Renderer.h"
#include "TGAImageWriter.h"

#include "Sphere.h"
#include "Plane.h"

#include <string>

/*
    Command line arguments:
        -w <width>
        -h <height>
        -s <number of pixel samples>
        -b <maximum number of bounces>
        -a <camera aperture>
        -f <focal length>
        -v <field of view>
*/

int main(int argc, char** argv) {
    Scene scene;

    int width = 100, height = 100;
    int samples = 4, depth = 16;
    double aperture = 0.0, focalLength = 100.0, fov = M_PI / 4;

    if (argc > 1) {
        int start = 1;
        for (int i = 1; i <= argc; ++i) {
            try {
                if (i >= argc || argv[i][0] == '-') {
                    switch (argv[start][1]) {
                        case 'w': {
                            if (i - start > 1) {
                                width = std::stoi(argv[start + 1]);
                            }
                            break;
                        }
                        case 'h': {
                            if (i - start > 1) {
                                height = std::stoi(argv[start + 1]);
                            }
                            break;
                        }
                        case 's': {
                            if (i - start > 1) {
                                samples = std::stoi(argv[start + 1]);
                            }
                            break;
                        }
                        case 'b': {
                            if (i - start > 1) {
                                depth = std::stoi(argv[start + 1]);
                            }
                            break;
                        }
                        case 'a': {
                            if (i - start > 1) {
                                aperture = std::stod(argv[start + 1]);
                            }
                            break;
                        }
                        case 'f': {
                            if (i - start > 1) {
                                focalLength = std::stod(argv[start + 1]);
                            }
                            break;
                        }
                        case 'v': {
                            if (i - start > 1) {
                                fov = std::stod(argv[start + 1]);
                            }
                            break;
                        }
                    }

                    // Setup for next iteration
                    start = i;
                }
            }
            catch (std::invalid_argument e) {
                printf("Couldn't parse argument (%s)", argv[start]);
            }
            catch (std::out_of_range e) {
                printf("Couldn't parse argument (%s)", argv[start]);
            }
        }
    }

    Sphere s1(Vector<3>({0, 0, -10}), 2);
    s1.setMaterial(Material(
        Vector<3>(), Vector<3>({0.9, 0, 0}), DIFFUSE
    ));
    scene.add(s1);

    Sphere light(Vector<3>({0, 2, -10}), 1);
    light.setMaterial(Material(
        Vector<3>({10, 10, 10}), Vector<3>({1, 1, 1}), DIFFUSE
    ));
    scene.add(light);

    Plane p1(Vector<3>({0, -1, 0}), Vector<3>({0, 1, 0}));
    p1.setMaterial(Material(
        Vector<3>(), Vector<3>({1, 1, 1}), DIFFUSE
    ));
    scene.add(p1);

    Camera camera(aperture, focalLength, fov);
    Renderer renderer(scene, camera, samples, depth);
    TGAImageWriter writer("output.tga");
    Image image = renderer.render(width, height);
    writer.write(image);
}