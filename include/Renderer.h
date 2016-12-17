#pragma once

#include "Image.h"
#include "Camera.h"
#include "Scene.h"

class Renderer {
private:
	Scene scene;
	Camera camera;
public:
	Image render(int w, int h);
}
