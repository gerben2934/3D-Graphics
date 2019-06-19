#include "GameObject.h"
#include "DrawComponent.h"
#include <GL/freeglut.h>

GameObject::GameObject(int objectId)
{
	this->ObjectId = objectId;
	glPushMatrix();
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	glPopMatrix();
}

GameObject::~GameObject()
{
}

void GameObject::reset()
{
	glPushMatrix();
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	glPopMatrix();
}

Vec3f GameObject::position()
{
	//[a,b,c,d]   [x]   | 
	//[e,f,g,h] * [y] = | 
	//[i,j,k,l]   [z]   |
	//[m,n,o,p]   [w]   |
	return Vec3f(matrix[12], matrix[13], matrix[14]);
}

void GameObject::printMatrix() {
	std::cout << "\r\nMatrix of GameObject: " << this->ObjectId;
	for (int i = 0; i < 16; i += 4) {
		std::cout << "\r\n " << matrix[i] << "," << matrix[i+1] << "," << matrix[i+2] << "," << matrix[i+3];
	}
}


void GameObject::translate(const Vec3f &pos)
{
	glPushMatrix();
	glLoadMatrixf(matrix);
	glTranslatef(pos.x, pos.y, pos.z);
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	glPopMatrix();
}

void GameObject::rotate(float angle, const Vec3f & axis)
{
	glPushMatrix();
	glLoadIdentity();
	glRotatef(angle, axis.x, axis.y, axis.z);
	glMultMatrixf(matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	glPopMatrix();
}

void GameObject::addComponent(Component* component)
{
	component->setGameObject(this);
	components.push_back(component);

	if (!drawComponent)
		drawComponent = dynamic_cast<DrawComponent*>(component);
}

std::list<Component*> GameObject::getComponents()
{
	return components;
}


void GameObject::draw()
{
	if (!drawComponent)
		return;

	glPushMatrix();
	glMultMatrixf(matrix);

	drawComponent->draw();
	glPopMatrix();
}

void GameObject::update(float elapsedTime)
{
	for (auto& c : components)
		c->update(elapsedTime);
}