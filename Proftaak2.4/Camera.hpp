#pragma once
struct Camera
{
	float posX;
	float posY;
	float rotX;
	float rotY;
	Camera() :posX(0), posY(0), rotX(0), rotY(0) {}
	Camera(float posX, float posY, float rotX, float rotY)
		: posX(posX), posY(posY), rotX(rotX), rotY(rotY) {}
};