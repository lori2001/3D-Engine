#pragma once
#include "SFML/Graphics.hpp"

struct triangle
{
	sf::Vector3f p[3];
};

struct mesh
{
	std::vector<triangle> tris;
};

struct mat4x4
{
	float m[4][4] = { 0 };
};