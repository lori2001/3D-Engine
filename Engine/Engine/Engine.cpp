#include "Engine.h"

void Engine::Setup()
{
	cubes.push_back(Cube{});
	cubes[0].move({ 0,0,-5.0f });
	cubes.push_back(Cube{});
	cubes[1].move({ -2.5f,0,-5.0f });
	surfaces.push_back(Surface{});
	surfaces[0].move({ 2.5f,0,-5.0f });
}

void Engine::handleEvents(const sf::Event & event)
{
}

void Engine::Update()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		cubes[0].move({0,0.1f,0});
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		cubes[0].move({ 0,-0.1f,0 });
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		cubes[0].move({ -0.1f,0,0 });
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		cubes[0].move({ 0.1f,0,0 });
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		cubes[0].move({ 0,0,-0.1f });
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		cubes[0].move({ 0,0,0.1f });

	surfaces[0].rotate(0.3f, { 0,1,0 });
	cubes[0].rotate(0.6f, { 1,1,0 });
	cubes[1].rotate(0.6f, { 1,1,0 });
}

void Engine::Compose()
{
	for(int i=0 ; i < int(cubes.size()); i++)
		cubes[i].draw();
	for (int i = 0; i < int(surfaces.size()); i++)
		surfaces[i].draw();
}

void Engine::setOGLViewport(const sf::Vector2u & size)
{
	// adjust the viewport when the window is resized
	glViewport(0, 0, size.x, size.y);

	// projects things in pseudo3D space
	glMatrixMode(GL_PROJECTION);
	// resets projection matrix to original
	glLoadIdentity();
	// calculates proper aspect ratio
	GLfloat ratio = static_cast<float>(size.x) / size.y;
	// creates the viewport with the given ratio
	// glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);
	perspectiveGL(90, ratio, 0.1f, 1000.0f);

	// draw only things that fit in the view space
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void Engine::perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
	const GLdouble pi = 3.1415926535897932384626433832795;
	GLdouble fW, fH;

	//fH = tan( (fovY / 2) / 180 * pi ) * zNear;
	fH = tan(fovY / 360 * pi) * zNear;
	fW = fH * aspect;

	glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}
