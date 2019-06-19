#pragma once

#include <list>
#include "Vec.h"
#include <iostream>

class Component;
class DrawComponent;

class GameObject
{
	DrawComponent* drawComponent = nullptr;
	int objectId;
	std::list<Component*> components;
public:
	GameObject(int objectId);
	~GameObject();

	float matrix[16];

	void reset();
	void translate(const Vec3f &pos);
	void rotate(float angle, const Vec3f &axis);
	Vec3f position();
	void printMatrix();

	int ObjectId;

	void addComponent(Component* component);
	std::list<Component*> getComponents();
	void update(float elapsedTime);
	void draw();

	template<class T>
	T* getComponent()
	{
		for (auto c : components)
		{
			T* t = dynamic_cast<T*>(c);
			if (t)
				return t;
		}
	}

	template<class T>
	void removeComponent()
	{
		components.remove_if([](Component * c)
		{
			T* t = dynamic_cast<T*>(c);
			return t != nullptr;
		});
	}
};