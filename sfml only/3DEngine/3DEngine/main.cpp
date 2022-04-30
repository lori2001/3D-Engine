#include <iostream>
#include <math.h>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Structs.h"

constexpr int WIDTH = 1000;
constexpr int HEIGHT = 600;

using namespace std;
using namespace sf;

void MultiplyMatrixVector(sf::Vector3f &i, sf::Vector3f &o, mat4x4 &m)
{
	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

	if (w != 0.0f) // just making sure nothing crashes
	{
		o.x /= w; o.y /= w; o.z /= w;
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "3D Demo");

	mesh meshCube;
	mat4x4 matProj;
	sf::Clock clock;

	float size = 1.0f;

	// SOUTH
	meshCube.tris.push_back(triangle{ Vector3f{0.0f, 0.0f, 0.0f}, Vector3f{0.0f, size, 0.0f}, Vector3f{size, size, 0.0f} });
	meshCube.tris.push_back(triangle{ Vector3f{0.0f, 0.0f, 0.0f}, Vector3f{size, size, 0.0f}, Vector3f{size, 0.0f, 0.0f} });

	// EAST
	meshCube.tris.push_back(triangle{ Vector3f{size, 0.0f, 0.0f}, Vector3f{size, size, 0.0f}, Vector3f{size, size, size} });
	meshCube.tris.push_back(triangle{ Vector3f{size, 0.0f, 0.0f}, Vector3f{size, size, size}, Vector3f{size, 0.0f, size} });

	// NORTH
	meshCube.tris.push_back(triangle{ Vector3f{size, 0.0f, size}, Vector3f{size, size, size}, Vector3f{0.0f, size, size} });
	meshCube.tris.push_back(triangle{ Vector3f{size, 0.0f, size}, Vector3f{0.0f, size, size}, Vector3f{0.0f, 0.0f, size} });

	// WEST
	meshCube.tris.push_back(triangle{ Vector3f{0.0f, 0.0f, size}, Vector3f{0.0f, size, size}, Vector3f{0.0f, size, 0.0f} });
	meshCube.tris.push_back(triangle{ Vector3f{0.0f, 0.0f, size}, Vector3f{0.0f, size, 0.0f}, Vector3f{0.0f, 0.0f, 0.0f} });

	// TOP                                                       
	meshCube.tris.push_back(triangle{ Vector3f{0.0f, size, 0.0f}, Vector3f{0.0f, size, size}, Vector3f{size, size, size} });
	meshCube.tris.push_back(triangle{ Vector3f{0.0f, size, 0.0f}, Vector3f{size, size, size}, Vector3f{size, size, 0.0f} });

	// BOTTOM                                                    
	meshCube.tris.push_back(triangle{ Vector3f{size, 0.0f, size}, Vector3f{0.0f, 0.0f, size}, Vector3f{0.0f, 0.0f, 0.0f} });
	meshCube.tris.push_back(triangle{ Vector3f{size, 0.0f, size}, Vector3f{0.0f, 0.0f, 0.0f}, Vector3f{size, 0.0f, 0.0f} });

	// Projection Matrix
	float fNear = 0.1f;
	float fFar = 1000.0f;
	float fFov = 90.0f;
	float fAspectRatio = (float)HEIGHT / (float)WIDTH;
	float fFovRad = 1.0f / atan2(fFov * 0.5f, 1 ); // 180.0f * 3.14159f
	float fTheta = 0;

	matProj.m[0][0] = fAspectRatio * fFovRad;
	matProj.m[1][1] = fFovRad;
	matProj.m[2][2] = fFar / (fFar - fNear);
	matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
	matProj.m[2][3] = 1.0f;
	matProj.m[3][3] = 0.0f;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Time elapsed = clock.restart();
		int fElapsedTime = elapsed.asMilliseconds();

		// Clear Screen
		window.clear();

		// Set up rotation matrices
		mat4x4 matRotZ, matRotX;
		fTheta += 0.001f * fElapsedTime;

		// Rotation Z
		matRotZ.m[0][0] = cosf(fTheta);
		matRotZ.m[0][1] = sinf(fTheta);
		matRotZ.m[1][0] = -sinf(fTheta);
		matRotZ.m[1][1] = cosf(fTheta);
		matRotZ.m[2][2] = 1;
		matRotZ.m[3][3] = 1;

		// Rotation X
		matRotX.m[0][0] = 1;
		matRotX.m[1][1] = cosf(fTheta * 0.5f);
		matRotX.m[1][2] = sinf(fTheta * 0.5f);
		matRotX.m[2][1] = -sinf(fTheta * 0.5f);
		matRotX.m[2][2] = cosf(fTheta * 0.5f);
		matRotX.m[3][3] = 1;

		window.clear();

		// Draw Triangles
		for (auto tri : meshCube.tris)
		{
			triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;
			
			// Rotate in Z-Axis
			MultiplyMatrixVector(tri.p[0], triRotatedZ.p[0], matRotZ);
			MultiplyMatrixVector(tri.p[1], triRotatedZ.p[1], matRotZ);
			MultiplyMatrixVector(tri.p[2], triRotatedZ.p[2], matRotZ);

			// Rotate in X-Axis
			MultiplyMatrixVector(triRotatedZ.p[0], triRotatedZX.p[0], matRotX);
			MultiplyMatrixVector(triRotatedZ.p[1], triRotatedZX.p[1], matRotX);
			MultiplyMatrixVector(triRotatedZ.p[2], triRotatedZX.p[2], matRotX);

			// Offset into the screen
			triTranslated = triRotatedZX;
			triTranslated.p[0].z = triRotatedZX.p[0].z + 3.0f;
			triTranslated.p[1].z = triRotatedZX.p[1].z + 3.0f;
			triTranslated.p[2].z = triRotatedZX.p[2].z + 3.0f;

			// Project triangles from 3D --> 2D
			MultiplyMatrixVector(triTranslated.p[0], triProjected.p[0], matProj);
			MultiplyMatrixVector(triTranslated.p[1], triProjected.p[1], matProj);
			MultiplyMatrixVector(triTranslated.p[2], triProjected.p[2], matProj);

			// Scale into view
			triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
			triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
			triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;
			triProjected.p[0].x *= 0.5f * (float)WIDTH;
			triProjected.p[0].y *= 0.5f * (float)HEIGHT;
			triProjected.p[1].x *= 0.5f * (float)WIDTH;
			triProjected.p[1].y *= 0.5f * (float)HEIGHT;
			triProjected.p[2].x *= 0.5f * (float)WIDTH;
			triProjected.p[2].y *= 0.5f * (float)HEIGHT;

			sf::ConvexShape convex;
			convex.setPointCount(3);

			convex.setPoint(0, sf::Vector2f(triProjected.p[0].x, triProjected.p[0].y));
			convex.setPoint(1, sf::Vector2f(triProjected.p[1].x, triProjected.p[1].y));
			convex.setPoint(2, sf::Vector2f(triProjected.p[2].x, triProjected.p[2].y));

			convex.setOutlineColor(sf::Color::White);
			convex.setFillColor(sf::Color::Transparent);
			convex.setOutlineThickness(1);
			window.draw(convex);
		}

		window.display();
	}

	return 0;
}