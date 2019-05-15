#pragma once
#include "SFML/Window.hpp"
#include "SFML/OpenGL.hpp"
#include "Surface.h"
#include "Cube.h"

class Engine
{
public:
	void Setup(); // setup
	void handleEvents(const sf::Event &event); // event handler
	void Update(); // logic
	void Compose(); // drawing

	void setOGLViewport(const sf::Vector2u& size);
	void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);
private:

	std::vector<Cube> cubes;
	std::vector<Surface> surfaces;
};