#include "Surface.h"

void Surface::move(sf::Vector3f offset)
{
	m_pos += offset;
}

void Surface::rotate(float offsetAngle, sf::Vector3f axis)
{
	m_angle += offsetAngle;
	m_rotation += axis;
}

void Surface::draw()
{
	transform();

	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 1);
	/*triangle 1*/
	glVertex3f(-m_size.x / 2, -m_size.y / 2, 0);
	glVertex3f(-m_size.x / 2, +m_size.y / 2, 0);
	glVertex3f(m_size.x / 2, -m_size.y / 2, 0);
	/*triangle 2*/
	glVertex3f(m_size.x / 2, m_size.y / 2, 0);
	glVertex3f(-m_size.x / 2, +m_size.y / 2, 0);
	glVertex3f(m_size.x / 2, -m_size.y / 2, 0);
	glEnd();
}

void Surface::transform()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // load original matrix

	glTranslatef(m_pos.x, m_pos.y, m_pos.z);

	// anchor point
	//glTranslatef(0, 0, 0);

	glRotatef(m_angle, m_rotation.x, m_rotation.y, m_rotation.z);

	// hozd vissza
	//glTranslatef(0, 0, -depth);
}
