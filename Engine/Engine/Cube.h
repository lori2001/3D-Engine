#pragma once
#include "SFML/Window.hpp"
#include "SFML/OpenGL.hpp"

class Cube
{
public:
	void move(sf::Vector3f offset); // moves entity by an offset
	void rotate(float offsetAngle, sf::Vector3f axis); // rotates entity on axis by angle offset

	//void setPosition(sf::Vector3f position);
	//void setRotation();

	void draw();
private:
	void transform(); // resets matrix and applies position

	sf::Vector3f m_pos{ 0,0,-3.0f }; // default position 3 units away from cam in z
	sf::Vector3f m_size{ 1,1,1 }; // default size 1,1,1

	float m_angle = 0.0f; // angle of rotation 
	sf::Vector3f m_rotation{ 0,0,0 }; // axis of rotation
};