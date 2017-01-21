#include "Scene.h"
#include "Renderer.h"
#include "TGAImageWriter.h"

#include "Sphere.h"
#include "Plane.h"

#include "utils.h"

#include <string>
#include <random>
#include <ctime>

/*
    Command line arguments:
        -w <width>
        -h <height>
        -s <number of pixel samples>
        -a <camera aperture>
        -f <focal length>
        -v <field of view>
*/

/*
PROFILING
- Compile and link with -pg flag
- Run once
- Use gprof -b -p for flat profile
- Use gprof -b -q for tree profile
*/

int main(int argc, char** argv) {
    Scene scene;

    int width = 800, height = 600;
    int samples = 16;
    double aperture = 0.0, focalLength = 100.0, fov = M_PI / 5;

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

    Plane floor(Vector<3>({0, -2, 0}), Vector<3>({0, 1, 0}));
    floor.setMaterial(Material(
        Vector<3>(), Vector<3>({.5, .5, .5}), DIFFUSE
    ));
    scene.add(floor);

    Sphere spheres[20];
    for (int i = 0; i < 20; ++i) {
        spheres[i] = Sphere(
            Vector<3>({3, -0.5, -i * 10.0}), 1.5
        );
        spheres[i].setMaterial(Material(
             Vector<3>(), Vector<3>({randd(), randd(), randd()}), DIFFUSE
        ));
        scene.add(spheres[i]);
    }

    srand(time(NULL));

    Camera camera(aperture, focalLength, fov);
    Renderer renderer(scene, camera, samples);
    Image image = renderer.render(width, height);
    TGAImageWriter writer("output.tga");
    writer.write(image);
}