#include <GL/freeglut.h>
#include "StageComponent.h"


StageComponent::StageComponent()
{
}

StageComponent::~StageComponent()
{
}

void StageComponent::draw()
{
	//RIGHT WALL
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(-3, -2, 2.5);
	glVertex3f(-3, -2, 100);
	glVertex3f(-3, 4, 100);
	glVertex3f(-3, 4, 2.5);
	glEnd();

	//START WALL RIGHT
	glBegin(GL_QUADS);
	glColor3f(1, 0, 1);
	glColor3f(0, 1, 0);
	glVertex3f(-2.5, -2, 2.49);
	glVertex3f(-3.5, -2, 2.49);
	glVertex3f(-3.5, 4, 2.49);
	glVertex3f(-2.5, 4, 2.49);
	glEnd();

	//LEFT WALL
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glVertex3f(3, -2, 2.5);
	glVertex3f(3, -2, 100);
	glVertex3f(3, 4, 100);
	glVertex3f(3, 4, 2.5);
	glEnd();

	//START WALL LEFT
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(2.5, -2, 2.49);
	glVertex3f(3.5, -2, 2.49);
	glVertex3f(3.5, 4, 2.49);
	glVertex3f(2.5, 4, 2.49);
	glEnd();

	//BASE PLATFORM
	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);
	glVertex3f(-2, 0.7, 1);
	glVertex3f(-2, 0.7, 100);
	glVertex3f(2, 0.7, 100);
	glVertex3f(2, 0.7, 1);
	glEnd();
}
