#include "Cube.h"

void Cube::move(sf::Vector3f offset)
{
	m_pos += offset;
}

void Cube::rotate(float offsetAngle, sf::Vector3f axis)
{
	m_angle += offsetAngle;
	m_rotation += axis;
}

void Cube::draw()
{
	transform();

	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 1);
	/*BACK*/
		/*triangle 1*/
		glVertex3f(-m_size.x / 2, -m_size.y / 2, -m_size.z / 2);
		glVertex3f(-m_size.x / 2, m_size.y / 2, -m_size.z / 2);
		glVertex3f(m_size.x / 2, -m_size.y / 2, -m_size.z / 2);
		/*triangle 2*/
		glVertex3f(m_size.x / 2, m_size.y / 2, -m_size.z / 2);
		glVertex3f(-m_size.x / 2, m_size.y / 2, -m_size.z / 2);
		glVertex3f(m_size.x / 2, -m_size.y / 2, -m_size.z / 2);
	glColor3f(0, 1, 1);
	/*FRONT*/
		/*triangle 1*/
		glVertex3f(-m_size.x / 2, -m_size.y / 2, m_size.z / 2);
		glVertex3f(-m_size.x / 2, m_size.y / 2, m_size.z / 2);
		glVertex3f(m_size.x / 2, -m_size.y / 2, m_size.z / 2);
		/*triangle 2*/
		glVertex3f(m_size.x / 2, m_size.y / 2, m_size.z / 2);
		glVertex3f(-m_size.x / 2, m_size.y / 2, m_size.z / 2);
		glVertex3f(m_size.x / 2, -m_size.y / 2, m_size.z / 2);
	glColor3f(1, 0, 1);
	/*TOP*/
		/*triangle 1*/
		glVertex3f(-m_size.x / 2, m_size.y / 2, -m_size.z / 2);
		glVertex3f(m_size.x / 2, m_size.y / 2, -m_size.z / 2);
		glVertex3f(m_size.x / 2, m_size.y / 2, m_size.z / 2);
		/*triangle 2*/
		glVertex3f(-m_size.x / 2, m_size.y / 2, -m_size.z / 2);
		glVertex3f(-m_size.x / 2, m_size.y / 2, m_size.z / 2);
		glVertex3f(m_size.x / 2, m_size.y / 2, m_size.z / 2);
	glColor3f(0, 1, 0);
	/*BOTTOM*/
		/*triangle 1*/
		glVertex3f(-m_size.x / 2, -m_size.y / 2, -m_size.z / 2);
		glVertex3f(m_size.x / 2, -m_size.y / 2, -m_size.z / 2);
		glVertex3f(m_size.x / 2, -m_size.y / 2, m_size.z / 2);
		/*triangle 2*/
		glVertex3f(-m_size.x / 2, -m_size.y / 2, -m_size.z / 2);
		glVertex3f(-m_size.x / 2, -m_size.y / 2, m_size.z / 2);
		glVertex3f(m_size.x / 2, -m_size.y / 2, m_size.z / 2);
	glColor3f(1, 0, 0);
	/*RIGHT (Camera)*/
		/*triangle 1*/
		glVertex3f(m_size.x / 2, m_size.y / 2, m_size.z / 2);
		glVertex3f(m_size.x / 2, m_size.y / 2, -m_size.z / 2);
		glVertex3f(m_size.x / 2, -m_size.y / 2, -m_size.z / 2);
		/*triangle 2*/
		glVertex3f(m_size.x / 2, m_size.y / 2, m_size.z / 2);
		glVertex3f(m_size.x / 2, -m_size.y / 2, m_size.z / 2);
		glVertex3f(m_size.x / 2, -m_size.y / 2, -m_size.z / 2);
	glColor3f(1, 1, 0);
	/*LEFT (CAMERA)*/
		/*triangle 1*/
		glVertex3f(-m_size.x / 2, m_size.y / 2, m_size.z / 2);
		glVertex3f(-m_size.x / 2, m_size.y / 2, -m_size.z / 2);
		glVertex3f(-m_size.x / 2, -m_size.y / 2, -m_size.z / 2);
		/*triangle 2*/
		glVertex3f(-m_size.x / 2, m_size.y / 2, m_size.z / 2);
		glVertex3f(-m_size.x / 2, -m_size.y / 2, m_size.z / 2);
		glVertex3f(-m_size.x / 2, -m_size.y / 2, -m_size.z / 2);
		glEnd();
}

void Cube::transform()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // load original matrix

	glTranslatef(m_pos.x, m_pos.y, m_pos.z);

	glRotatef(m_angle, m_rotation.x, m_rotation.y, m_rotation.z);
}
