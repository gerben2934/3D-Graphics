#pragma once
#include <GL\freeglut.h>
#include "DrawComponent.h"
#include "Enums.h"

class CubeComponent : public DrawComponent
{


public:
	CubeComponent(float size, int cubeId, GLuint textureID, bool center, bool edge, bool corner);// , double startPos, double endPos); //, int startPos, int endPos);// , GLuint textureID, int startPos, int endPos);
	~CubeComponent();
	float getTextureX(int color);
	float getTextureY(int color);
	virtual void draw() override;
	float size;
	GLuint textureID;
	int cubeId;
	bool center;
	bool edge;
	bool corner;
	bool swapped;
	//void drawWithTexture(GLuint textureID, int size, int startPos, int endPos);
};