#include "Scene.h"
#include "Renderer.h"
#include "TGAImageWriter.h"

int main(int argc, char** argv) {
    Scene scene;
    Camera camera(0, 0, M_PI / 4);
    Renderer renderer(scene, camera);
    TGAImageWriter writer("output.tga");
    writer.write(renderer.render(100, 200));
}