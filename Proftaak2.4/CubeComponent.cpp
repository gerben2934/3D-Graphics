#include "CubeComponent.h"
#include "ObjectModel.h"
#include <GL/freeglut.h>
#include <iostream>
#include "Enums.h"

int textureID;

float u, v, u2, v2;
const float DELTASIZE = 0.33f;

CubeComponent::CubeComponent(float size, int cubeId, GLuint textureID) {
	this->size = size;
	this->textureID = textureID;
	this->cubeId = cubeId;
}

CubeComponent::~CubeComponent() {
}

float CubeComponent::getTextureX(int textureNumber) {
	if (textureNumber % 3 == 0) { //0, 3, 6
		return 0;
	}
	else if (textureNumber % 3 == 1) { //1, 4, 7
		return 0.33f;
	}
	else {
		return 0.66f;
	}
}

float CubeComponent::getTextureY(int textureNumber) {
	if (textureNumber > 5) {
		return (float) 0.66f;
	}
	else if (textureNumber > 2) {
		return (float) 0.33f;
	}
	else {
		return 0;
	}
}

void CubeComponent::draw() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBlendFunc(GL_ONE, GL_ZERO);

	u = getTextureX(4);
	v = getTextureY(4);
	u2 = (u + DELTASIZE);
	v2 = (v + DELTASIZE);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(u, v); //LB
	glVertex3f(-size, -size, -size);
	glTexCoord2f(u, v2); //RB
	glVertex3f(size, -size, -size);
	glTexCoord2f(u2, v2); //RO
	glVertex3f(size, size, -size);
	glTexCoord2f(u2, v); //LO
	glVertex3f(-size, size, -size);
	glEnd();

	//back
	u = getTextureX(5);
	v = getTextureY(5);
	u2 = (u + DELTASIZE);
	v2 = (v + DELTASIZE);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(u, v);
	glVertex3f(-size, -size, size);
	glTexCoord2f(u, v2);
	glVertex3f(size, -size, size);
	glTexCoord2f(u2, v2);
	glVertex3f(size, size, size);
	glTexCoord2f(u2, v);
	glVertex3f(-size, size, size);
	glEnd();

	//left
	u = getTextureX(3);
	v = getTextureY(3);
	u2 = (u + DELTASIZE);
	v2 = (v + DELTASIZE);
	glBegin(GL_QUADS);
	glTexCoord2f(u, v);
	glVertex3f(-size, -size, -size);
	glTexCoord2f(u, v2);
	glVertex3f(-size, size, -size);
	glTexCoord2f(u2, v2);
	glVertex3f(-size, size, size);
	glTexCoord2f(u2, v);
	glVertex3f(-size, -size, size);
	glEnd();

	//right
	u = getTextureX(2);
	v = getTextureY(2);
	u2 = (u + DELTASIZE);
	v2 = (v + DELTASIZE);
	glBegin(GL_QUADS);
	glTexCoord2f(u, v);
	glVertex3f(size, -size, -size);
	glTexCoord2f(u, v2);
	glVertex3f(size, size, -size);
	glTexCoord2f(u2, v2);
	glVertex3f(size, size, size);
	glTexCoord2f(u2, v);
	glVertex3f(size, -size, size);
	glEnd();

	//bottom
	u = getTextureX(1);
	v = getTextureY(1);
	u2 = (u + DELTASIZE);
	v2 = (v + DELTASIZE);
	glBegin(GL_QUADS);
	glTexCoord2f(u, v);
	glVertex3f(-size, -size, -size);
	glTexCoord2f(u, v2);
	glVertex3f(size, -size, -size);
	glTexCoord2f(u2, v2);
	glVertex3f(size, -size, size);
	glTexCoord2f(u2, v);
	glVertex3f(-size, -size, size);
	glEnd();

	//top
	if (cubeId == 17) {
		u = getTextureX(6);
		v = getTextureY(6);
	}
	else {
		u = getTextureX(0);
		v = getTextureY(0);
	}

	u2 = (u + DELTASIZE);
	v2 = (v + DELTASIZE);
	glBegin(GL_QUADS);
	glTexCoord2f(u, v);
	glVertex3f(-size, size, -size);
	glTexCoord2f(u, v2);
	glVertex3f(size, size, -size);
	glTexCoord2f(u2, v2);
	glVertex3f(size, size, size);
	glTexCoord2f(u2, v);
	glVertex3f(-size, size, size);
	glDisable(GL_TEXTURE_2D);

	glEnd();
}