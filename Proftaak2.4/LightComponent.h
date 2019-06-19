#pragma once

#include <GL\freeglut.h>
#include "DrawComponent.h"
#include "Vec.h"

class LightComponent : public DrawComponent
{
public: 
	LightComponent(Vec3f, int);
	virtual void draw() override;
private:


	Vec3f position;
	int brightness;

};