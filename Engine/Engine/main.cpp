#include "SFML/Window.hpp"
#include "SFML/OpenGL.hpp"
#include "Engine.h"

int main()
{
	sf::ContextSettings settings;
	settings.depthBits = 24; // depth is held on 24 bits of space (float)
	settings.stencilBits = 8; // harmadik buffer (osszenyomja a kepet) (magatol nem fog rajzolni)
	settings.antialiasingLevel = 4;
	settings.majorVersion = 1;
	settings.minorVersion = 1;

	// create the window
	sf::Window window(sf::VideoMode(800, 600), "OpenGL Engine", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true); // limit framerate

	Engine engine;
	engine.Setup();

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClearDepth(1.0f);

	// initializes everything with the right size
	engine.setOGLViewport(window.getSize());

	// activates window
	window.setActive(true);

	bool running = true;
	while (running)
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				// end the program
				running = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				engine.setOGLViewport({ event.size.width, event.size.height });
			}

			engine.handleEvents(event);
		}

		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		engine.Update();
		engine.Compose();

		// end the current frame (internally swaps the front and back buffers)
		window.display();
	}

	return 0;
}