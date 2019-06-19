#include "ObjectModel.h"
#include "CubeComponent.h"
#include "LightComponent.h"

LightComponent::LightComponent(Vec3f pos, int brightness) { 

}

void LightComponent::draw() {	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glEnable(GL_LIGHTING);
	GLfloat light_position[] = { -6.0f,6.0f,6.0f, 0.5f};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	GLfloat light_diff[] = { 1.0, 1.0, 1.0, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diff);
	GLfloat light_amb[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
}