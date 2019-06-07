#include "MoveToComponent.h"
#include "GameObject.h"


MoveToComponent::MoveToComponent()
{
}


MoveToComponent::~MoveToComponent()
{
}

void MoveToComponent::update(float elapsedTime)
{
	/*gameObject->position.x = (1 - speed) * gameObject->position.x + speed * target.x;
	gameObject->position.y = (1 - speed) * gameObject->position.y + speed * target.y;
	gameObject->position.z = (1 - speed) * gameObject->position.z + speed * target.z;*/

	Vec3f diff = target - gameObject->position;
	if (diff.length() > speed * elapsedTime)
	{
		diff = diff.normalized();


		gameObject->position.x = gameObject->position.x + speed * diff.x * elapsedTime;
		gameObject->position.y = gameObject->position.y + speed * diff.y * elapsedTime;
		gameObject->position.z = gameObject->position.z + speed * diff.z * elapsedTime;
	}
	else
	{
		gameObject->position = target;
	}
}
