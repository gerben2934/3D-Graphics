#pragma once
#include <GL\freeglut.h>
#include "DrawComponent.h"
#include "Enums.h"

class CubeComponent : public DrawComponent
{


public:
	CubeComponent(float size, int cubeId, GLuint textureID);
	~CubeComponent();
	float getTextureX(int color);
	float getTextureY(int color);
	virtual void draw() override;
	float size;
	GLuint textureID;
	int cubeId;
};