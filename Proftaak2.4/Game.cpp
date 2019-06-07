#include "Game.hpp"
#include <list>
#include <iostream>
#include <GL\freeglut.h>
#include <vector>
#include <algorithm>

#include "Camera.hpp"
#include "GameObject.h"
#include "CubeComponent.h"

using namespace std;

namespace Game
{
	int windowWidth, windowHeight;

	Camera camera;
	std::vector<GameObject*> objects;
	std::vector<GameObject*> objectsInLayer;
	std::vector<GameObject*> cornersInLayer;
	std::vector<GameObject*> edgesInLayer;
	std::vector<int> centerIndexes{ 5, 11, 13, 15, 17, 23 };
	std::vector<int> edgeIndexes{ 2, 4, 6, 8, 10, 12, 16, 18, 20, 22, 24, 26 };
	std::vector<int> cornerIndexes = { 1, 3, 7, 9, 19, 21, 25, 27 };

	GameObject* blockPositions[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];

	void createRubicsCube(float size = 1.0f);

	void loadContent()
	{
		camera = Camera(0, 0, 0, 0);
		GameObject* room = new GameObject(0);
		objects.push_back(room);

		//EXAMPLE CUBES
		createRubicsCube(1.0f);
	}

	void update(float deltaTime) {
		for (const auto& o : objects)
		{
			o->draw();
			o->update(deltaTime);
		}
	}

	bool checkForInteger(std::vector<int> vector, int key) {
		if (std::find(vector.begin(), vector.end(), key) != vector.end()) {
			cout << "\r\n Found it!";
			return true;
		}
		return false;
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

	void createRubicsCube(float size) {
		//layer 1: 9 objects
		int cubeId = 1;
		int centers = 0;
		int corners = 0;
		int edges = 0;

		for (int z = 0; z < CUBE_SIZE; z++) {
			for (int y = 0; y < CUBE_SIZE; y++) {
				for (int x = 0; x < CUBE_SIZE; x++) {
					GameObject* cube = new GameObject(cubeId);
					if (x != 1 && y != 1 && z != 1) {
						CubeComponent* component = new CubeComponent(size, cubeId, 1, false, false, true);
						cube->addComponent(component);
						corners++;
					}
					else if ((x == 1 && z == 1) || (x == 1 && y == 1)) {
						CubeComponent* component = new CubeComponent(size, cubeId, 1, true, false, false);
						cube->addComponent(component);
						centers++;
					}
					else {
						CubeComponent* component = new CubeComponent(size, cubeId, 1, false, true, false);
						cube->addComponent(component);
						edges++;
					}
					Vec3f vector = Vec3f(x + x * size, y + y * size, z + z * size);

					cube->position = vector;
					blockPositions[x][y][z] = cube;
					objects.push_back(cube);
					cubeId++;
					cout << "\r\nCorners: " << corners << " edges: " << edges << " centers: " << centers;
				}
			}
		}
		cout << "\r\nObjectCount: " << objects.size();
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

		cout << "\r\nRotate F():";
		Vec3f blockPositionsInLayer[CUBE_SIZE][CUBE_SIZE];

		int cornerRotations = 0;
		int edgeRotations = 0;

		for (auto obj : objects)
		{
			//lijst met laag, hieraan dit obj toevoegen. 
			if (obj->ObjectId > 0) {
				if (obj->position.z == 4) {
					obj->rotation.z -= 90;
					
					//obj->rotation.y -= 90;

					//laag bekend
					objectsInLayer.push_back(obj);
					int cubeId = obj->getComponent<CubeComponent>()->cubeId;

					//cout << "\r\nObjectID: " << obj->ObjectId;
					//cout << "\r\nObject at: " << obj->position.x << "," << obj->position.y << "," << obj->position.z;

					if (obj->getComponent<CubeComponent>()->corner) {
						//cout << "\r\n Found corner! at: " << cubeId;
						cornersInLayer.push_back(obj);
					}
					else if (obj->getComponent<CubeComponent>()->edge) {
						//cout << "\r\n Found edge! at: " << cubeId;
						edgesInLayer.push_back(obj);
					}
				}
			}
		}

		for (auto obj : cornersInLayer) {
			//cout << "\r\nObj isCorner(): " << obj->getComponent<CubeComponent>()->corner;
			//cout << "\r\nPos: x: " << obj->position.x << " y: " << obj->position.y << " z: " << obj->position.z;
			if ((obj->position.x == 0) && (obj->position.y == 0)) { //links onder --> links boven
				//cout << "\r\n Links onder";
				obj->position.y = 4;
				//blockPositionsInLayer[0][0] = obj->position;
				cornerRotations++;

			}
			else if ((obj->position.x == 0) && (obj->position.y == 4)) { //links boven --> rechts boven
				//cout << "\r\n Links boven";
				obj->position.x = 4;
				//blockPositionsInLayer[0][4 / 2] = obj->position;
				cornerRotations++;
			}
			else if ((obj->position.x == 4) && (obj->position.y == 4)) { //rechts boven --> rechts onder
				//cout << "\r\r Rechts boven";
				obj->position.y = 0;
				//blockPositionsInLayer[4/2][4 / 2] = obj->position;
				cornerRotations++;

			}
			else if ((obj->position.x == 4) && (obj->position.y == 0)) { //rechts onder --> links onder
				//cout << "\r\n Rechts onder";
				obj->position.x = 0;
				//blockPositionsInLayer[4/2][0] = obj->position;
				cornerRotations++;
			}
		}

		for (auto obj : edgesInLayer) {
			//cout << "\r\nObj isEdge(): " << obj->getComponent<CubeComponent>()->edge;
			//cout << "\r\nPos: x: " << obj->position.x << " y: " << obj->position.y << " z: " << obj->position.z;
			if ((obj->position.x == 2) && (obj->position.y == 0)) { //onder --> links
				//cout << "\r\n Onder";
				obj->position.x = 0;
				obj->position.y = 2;
				//blockPositionsInLayer[1][0] = obj->position;
				edgeRotations++;
			}
			else if ((obj->position.x == 0) && (obj->position.y == 2)) { //links --> boven
				//cout << "\r\n Links";
				obj->position.x = 2;
				obj->position.y = 4;
				//blockPositionsInLayer[0][1] = obj->position;
				edgeRotations++;
			}
			else if ((obj->position.x == 2) && (obj->position.y == 4)) { //boven --> rechts
				//cout << "\r\r Boven";
				obj->position.x = 4;
				obj->position.y = 2;
				//blockPositionsInLayer[1][2] = obj->position;
				edgeRotations++;
			}
			else if ((obj->position.x == 4) && (obj->position.y == 2)) { //rechts --> onder
				//cout << "\r\n Rechts";
				obj->position.x = 2;
				obj->position.y = 0;
				//blockPositionsInLayer[2][1] = obj->position;
				edgeRotations++;


			}
		}

		cout << "\r\nObjects: \r\n";
		for (auto obj : objectsInLayer) {
			cout << ", Object: " << obj->ObjectId;
			//obj->position.z++;
		}

		cout << "\r\n ObjectsInLayer: " << objectsInLayer.size();
		cout << "\r\n Edgerotations: " << edgeRotations;
		cout << "\r\n Cornerrotations: " << cornerRotations;

		/*int z = 2;

		for (int y = 0; y < CUBE_SIZE - 1; y++) {
			for (int x = 0; x < CUBE_SIZE - 1; x++) {
				blockPositions[x][y][z] = blockPositionsInLayer[x][y]
			}
		}*/


		//cout << "\r\n After:";

		//cout << "\r\n==============================================\r\n";
		//for (int y = CUBE_SIZE - 1; y != -1; y--) {
		//	cout << "\r\n|" << blockPositions[0][y][2] << " | " << "|" << blockPositions[1][y][2] << " | " << "|" << blockPositions[2][y][2] << " | ";
		//}
		//cout << "\r\n==============================================\r\n";

		objectsInLayer.clear();
		cornersInLayer.clear();
		edgesInLayer.clear();
	}

	void rotateCubeB(bool clockWise) {
		for (auto obj : objects)
		{
			//lijst met laag, hieraan dit obj toevoegen. 
			if (obj->ObjectId > 0) {
				if (obj->position.z == 0) {
					obj->rotation.z += 90;
					//laag bekend
					objectsInLayer.push_back(obj);
					int cubeId = obj->getComponent<CubeComponent>()->cubeId;

					cout << "\r\nObjectID: " << obj->ObjectId;
					cout << "\r\nObject at: " << obj->position.x << "," << obj->position.y << "," << obj->position.z;

					if (obj->getComponent<CubeComponent>()->corner) {
						cout << "\r\n Found corner! at: " << cubeId;
						cornersInLayer.push_back(obj);
					}
					else if (obj->getComponent<CubeComponent>()->edge) {
						cout << "\r\n Found edge! at: " << cubeId;
						edgesInLayer.push_back(obj);
					}
				}
			}
		}

		for (auto obj : cornersInLayer) {
			cout << "\r\nObj isCorner(): " << obj->getComponent<CubeComponent>()->corner;
			cout << "\r\nPos: x: " << obj->position.x << " y: " << obj->position.y << " z: " << obj->position.z;
			if ((obj->position.x == 0) && (obj->position.y == 0)) { //rechts onder --> links onder
				cout << "\r\n Rechts onder";
				obj->position.x = 4;
			}
			else if ((obj->position.x == 0) && (obj->position.y == 4)) { //rechts boven --> rechts onder
				cout << "\r\n Rechts boven";
				obj->position.y = 0;
			}
			else if ((obj->position.x == 4) && (obj->position.y == 4)) { //links boven --> rechts boven 
				cout << "\r\r Links boven";
				obj->position.x = 0;
			}
			else if ((obj->position.x == 4) && (obj->position.y == 0)) { //links onder --> links boven
				cout << "\r\n Links onder";
				obj->position.y = 4;
			}
		}

		objectsInLayer.clear();
		cornersInLayer.clear();
		edgesInLayer.clear();
	}

	//void rotateCubeL(bool clockWise) {
	//	for (const auto& obj : objects)
	//	{
	//		//lijst met laag, hieraan dit obj toevoegen. 
	//		if (obj->position.x == 0) {
	//			objectsInLayer.push_back(obj);
	//		}
	//	}
	//	cout << "\r\nLeft face layout: ";
	//	for (const auto& obj : objectsInLayer) {
	//		cout << "\r\nObjectID: " << obj->ObjectId;
	//		cout << "\r\nObject at: " << obj->position.x << "," << obj->position.y << "," << obj->position.z;
	//		if (clockWise) {
	//			obj->rotation.x += 90;
	//		}
	//		else {
	//			obj->rotation.x -= 90;
	//		}
	//	}
	//	objectsInLayer.clear();
	//}

	void rotateCubeR(bool clockWise) {

		int cornerRotations = 0;
		int edgeRotations = 0;
		for (auto obj : objects)
		{
			//lijst met laag, hieraan dit obj toevoegen. 
			if (obj->ObjectId > 0) {
				if (obj->position.x == 4) {
					obj->rotation.x -= 90;

					//laag bekend
					objectsInLayer.push_back(obj);
					int cubeId = obj->getComponent<CubeComponent>()->cubeId;

					cout << "\r\nObjectID: " << obj->ObjectId;
					cout << "\r\nObject at: " << obj->position.x << "," << obj->position.y << "," << obj->position.z;

					if (obj->getComponent<CubeComponent>()->corner) {
						//cout << "\r\n Found corner! at: " << cubeId;
						cornersInLayer.push_back(obj);
					}
					else if (obj->getComponent<CubeComponent>()->edge) {
						//cout << "\r\n Found edge! at: " << cubeId;
						edgesInLayer.push_back(obj);
					}
				}
			}
		}

		for (auto obj : cornersInLayer) {
			cout << "\r\nObj isCorner(): " << obj->getComponent<CubeComponent>()->corner;
			cout << "\r\nPos: x: " << obj->position.x << " y: " << obj->position.y << " z: " << obj->position.z;
			if ((obj->position.z == 4) && (obj->position.y == 0)) { //links onder --> links boven
				cout << "\r\n Links onder";
				obj->position.y = 4;
				cornerRotations++;
			}
			else if ((obj->position.z == 4) && (obj->position.y == 4)) { //links boven --> rechts boven
				cout << "\r\n Links boven";
				obj->position.z = 0;
				cornerRotations++;

			}
			else if ((obj->position.z == 0) && (obj->position.y == 4)) { //rechts boven --> rechts onder
				cout << "\r\r Rechts boven";
				obj->position.y = 0;
				cornerRotations++;

			}
			else if ((obj->position.z == 0) && (obj->position.y == 0)) { //rechts onder --> links onder
				cout << "\r\n Rechts onder";
				obj->position.z = 4;
				cornerRotations++;
			}
		}

		for (auto obj : edgesInLayer) {
			//cout << "\r\nObj isEdge(): " << obj->getComponent<CubeComponent>()->edge;
			//cout << "\r\nPos: x: " << obj->position.x << " y: " << obj->position.y << " z: " << obj->position.z;
			if ((obj->position.z == 2) && (obj->position.y == 0)) { //onder --> links
				//cout << "\r\n Onder";
				obj->position.z = 4;
				obj->position.y = 2;
				//blockPositionsInLayer[1][0] = obj->position;
				edgeRotations++;
			}
			else if ((obj->position.z == 4) && (obj->position.y == 2)) { //links --> boven
				//cout << "\r\n Links";
				obj->position.z = 2;
				obj->position.y = 4;
				//blockPositionsInLayer[0][1] = obj->position;
				edgeRotations++;

			}
			else if ((obj->position.z == 2) && (obj->position.y == 4)) { //boven --> rechts
				//cout << "\r\r Boven";
				obj->position.z = 0;
				obj->position.y = 2;
				//blockPositionsInLayer[1][2] = obj->position;
				edgeRotations++;

			}
			else if ((obj->position.z == 0) && (obj->position.y == 2)) { //rechts --> onder
				//cout << "\r\n Rechts";
				obj->position.z = 2;
				obj->position.y = 0;
				//blockPositionsInLayer[2][1] = obj->position;
				edgeRotations++;


			}
		}

		for (auto obj : objectsInLayer) {
			cout << ", Object: " << obj->ObjectId;
			//obj->position.x++;
		}

		cout << "\r\n ObjectsInLayer: " << objectsInLayer.size();
		cout << "\r\n Edgerotations: " << edgeRotations;
		cout << "\r\n Cornerrotations: " << cornerRotations;


		objectsInLayer.clear();
		cornersInLayer.clear();
		edgesInLayer.clear();
	}
}

//void rotateCubeU(bool clockWise) {
//	for (const auto& obj : objects)
//	{
//		//lijst met laag, hieraan dit obj toevoegen. 
//		if (obj->position.y == 4) {
//			objectsInLayer.push_back(obj);
//		}
//	}

//	cout << "\r\nUp face layout: ";
//	for (const auto& obj : objectsInLayer) {
//		cout << "\r\nObjectID: " << obj->ObjectId;
//		cout << "\r\nObject at: " << obj->position.x << "," << obj->position.y << "," << obj->position.z;
//		if (clockWise) {
//			obj->rotation.y -= 90;
//		}
//		else {
//			obj->rotation.y += 90;
//		}
//	}
//	objectsInLayer.clear();
//}
//void rotateCubeD(bool clockWise) {
//	for (const auto& obj : objects)
//	{
//		//lijst met laag, hieraan dit obj toevoegen. 
//		if (obj->position.y == 0) {
//			objectsInLayer.push_back(obj);
//		}
//	}

//	cout << "\r\nDown face layout: ";
//	for (const auto& obj : objectsInLayer) {
//		cout << "\r\nObjectID: " << obj->ObjectId;
//		cout << "\r\nObject at: " << obj->position.x << "," << obj->position.y << "," << obj->position.z;

//		if (clockWise) {
//			obj->rotation.y += 90;
//		}
//		else {
//			obj->rotation.y -= 90;
//		}
//	}
//	objectsInLayer.clear();
//}
//}