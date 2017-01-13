#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include "Image.h"
#include "Camera.h"
#include "Scene.h"

class Renderer {
private:
	Scene scene;
	Camera camera;
	int samples;
	int depth;

public:
	Renderer(Scene s, Camera c, int spp = 4) : scene(s), camera(c), samples(spp) {};
	Image render(int w, int h);
};

#endif