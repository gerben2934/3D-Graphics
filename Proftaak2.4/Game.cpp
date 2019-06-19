#include "Game.hpp"
#include <list>
#include <iostream>
#include <GL\freeglut.h>
#include <vector>
#include <algorithm>

#include "Camera.hpp"
#include "GameObject.h"
#include "CubeComponent.h"
#include "LightComponent.h"

using namespace std;

namespace Game
{
	int windowWidth, windowHeight;

	Camera camera;
	std::vector<GameObject*> objects;
	std::vector<GameObject*> objectsInLayer;
	std::vector<GameObject*> cornersInLayer;
	std::vector<GameObject*> edgesInLayer;
	void createRubicsCube(float size = 1.0f);
	void createRoom(void);

	bool turning = false;

	Vec3f mult(float* mat, const Vec3f &v)
	{
		return Vec3f(
			mat[0] * v.x + mat[4] * v.y + mat[8] * v.z + mat[12],
			mat[1] * v.x + mat[5] * v.y + mat[9] * v.z + mat[13],
			mat[2] * v.x + mat[6] * v.y + mat[10] * v.z + mat[14]
		);
	}

	void loadContent()
	{
		glShadeModel(GL_SMOOTH);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		camera = Camera(10, 0, 0, 0);
		createRoom();
		createRubicsCube(1.0f);
	}

	int currentTime = 0;
	int newTime = 0;

	void update(float deltaTime) {
		for (const auto& o : objects)
		{
			o->update(deltaTime);
		}
	}

	void draw() {
		for (const auto& o : objects)
			o->draw();
	}

	void onResize(int w, int h) {
		windowWidth = w;
		windowHeight = h;
	}

	void onClose() {
		std::cout << "Cleaning up game\n";

		for (auto& o : objects)
			delete o;
		objects.clear();

		std::cout << "Closing game.\n";
	}

	void createRoom() {
		GameObject* room = new GameObject(0);
		room->addComponent(new LightComponent(Vec3f(0, 0, 0), 1.0f));
		objects.push_back(room);
	}

	void createRubicsCube(float size) {
		//layer 1: 9 objects
		int cubeId = 1;

		for (int z = 0; z < CUBE_SIZE; z++) {
			for (int y = 0; y < CUBE_SIZE; y++) {
				for (int x = 0; x < CUBE_SIZE; x++) {
					GameObject* cube = new GameObject(cubeId);
					if (x != 1 && y != 1 && z != 1) {
						CubeComponent* component = new CubeComponent(size, cubeId, 1);
						cube->addComponent(component);
					}
					else if ((x == 1 && z == 1) || (x == 1 && y == 1)) {
						CubeComponent* component = new CubeComponent(size, cubeId, 1);
						cube->addComponent(component);
					}
					else {
						CubeComponent* component = new CubeComponent(size, cubeId, 1);
						cube->addComponent(component);
					}
					Vec3f vector = Vec3f(2 * x - 2, 2 * y - 2, 2 * z - 2);
					cube->translate(vector);
					objects.push_back(cube);
					cubeId++;
				}
			}
		}
		cout << "\r\nObjectCount: " << objects.size();
	}

	void resetRubiks() {
		for (auto& o : objects)
			delete o;
		objects.clear();
		createRubicsCube(1.0f);

		cout << "\r\n Cube reset!";
	}

	//			    ++
	//				Y
	//				|
	//				|
	//				|
	//				|
	//				|
	//				|
	//				|
	//				+_________________X++
	//				/
	//			   /
	//			  /
	//			 /
	//		    /
	//		   Z
	//		  ++

	void rotateCubeF(bool clockWise) {
		if (!turning) {
			turning = true;
			cout << "\r\nRotate F():";
			for (auto obj : objects)
			{
				//lijst met laag, hieraan dit obj toevoegen. 
				if (obj->ObjectId > 0) {
					Vec3f pos = obj->position();
					if (fabs(pos.z - 2) < 0.01) {
						objectsInLayer.push_back(obj);
					}
				}
			}

			//for (int i = 0; i < 9; i++) {

			for (auto obj : objectsInLayer) {
				obj->rotate(-90, Vec3f(0, 0, 1));
			}
			//}

			objectsInLayer.clear();
			turning = false;
		}
	}

	void rotateCubeB(bool clockWise) {
		if (!turning) {
			turning = true;
			cout << "\r\nRotate B():";
			for (auto obj : objects)
			{
				//lijst met laag, hieraan dit obj toevoegen. 
				if (obj->ObjectId > 0) {
					Vec3f pos = obj->position();
					if (fabs(pos.z + 2) < 0.01) {
						objectsInLayer.push_back(obj);
					}
				}
			}

			for (auto obj : objectsInLayer) {
				obj->rotate(90, Vec3f(0, 0, 1));
			}

			objectsInLayer.clear();
			turning = false;
		}
	}

	void rotateCubeL(bool clockWise) {
		if (!turning) {
			turning = true;
			cout << "\r\nRotate L():";
			for (auto obj : objects)
			{
				//lijst met laag, hieraan dit obj toevoegen. 
				if (obj->ObjectId > 0) {
					Vec3f pos = obj->position();
					if (fabs(pos.x + 2) < 0.01) {
						objectsInLayer.push_back(obj);
					}
				}
			}

			//for (int i = 0; i < 9; i++) {
			for (auto obj : objectsInLayer) {
				obj->rotate(90, Vec3f(1, 0, 0));
			}
			//}

			objectsInLayer.clear();
			turning = false;
		}
	}

	void rotateCubeR(bool clockWise) {
		if (!turning) {
			turning = true;
			cout << "\r\nRotate R():";
			for (auto obj : objects)
			{
				//lijst met laag, hieraan dit obj toevoegen. 
				if (obj->ObjectId > 0) {
					Vec3f pos = obj->position();
					if (fabs(pos.x - 2) < 0.01) {
						objectsInLayer.push_back(obj);
					}
				}
			}

			//for (int i = 0; i < 9; i++) {
			for (auto obj : objectsInLayer) {
				obj->rotate(-90, Vec3f(1, 0, 0));
			}
			//}

			objectsInLayer.clear();
			turning = false;
		}
	}

	void rotateCubeU(bool clockWise) {
		if (!turning) {
			turning = true;
			cout << "\r\nRotate U():";
			for (auto obj : objects)
			{
				//lijst met laag, hieraan dit obj toevoegen. 
				if (obj->ObjectId > 0) {
					Vec3f pos = obj->position();
					if (fabs(pos.y - 2) < 0.01) {
						objectsInLayer.push_back(obj);
					}
				}
			}

			//for (int i = 0; i < 9; i++) {
			for (auto obj : objectsInLayer) {
				obj->rotate(-90, Vec3f(0, 1, 0));
			}
			//}

			objectsInLayer.clear();
			turning = false;
		}
	}

	void rotateCubeD(bool clockWise) {
		if (!turning) {
			turning = true;
			cout << "\r\nRotate U():";
			for (auto obj : objects)
			{
				//lijst met laag, hieraan dit obj toevoegen. 
				if (obj->ObjectId > 0) {
					Vec3f pos = obj->position();
					if (fabs(pos.y + 2) < 0.01) {
						objectsInLayer.push_back(obj);
					}
				}
			}

			//for (int i = 0; i < 9; i++) {
			for (auto obj : objectsInLayer) {
				obj->rotate(90, Vec3f(0, 1, 0));
			}
			//}

			objectsInLayer.clear();
			turning = false;
		}
	}
}