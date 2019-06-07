#ifndef GAME_HPP
#define GAME_HPP
#include "Globals.hpp"
#include "GameObject.h"
#include "Vec.h"
#include "Enums.h"
#include <vector>

using namespace std;


namespace Game
{
	const int CUBE_SIZE = 3;

	// Needs to be publicly available for modules etc.
	extern bool keys[256];
	// Gets called when the engine is ready to load in content / initialize.
	void loadContent();
	// Gets called every frame for game logic.
	void update(float deltaTime);
	// Gets called on every draw.
	void draw();
	// Gets called when a key gets pressed.
	void onKey(Key key);
	// Gets called when a key is released.
	void onKeyUp(Key key);
	// Gets called when the mouse moves.
	void onMouseMove(int x, int y);
	// Gets called when the screen resizes.
	void onResize(int w, int h);
	// Gets called when app is closing.
	void onClose();

	bool checkForInteger(std::vector<int> vector, int key);

	//Rotation functions:
	void rotateCubeF(bool clockWise);
	void rotateCubeB(bool clockWise);
	void rotateCubeL(bool clockWise);
	void rotateCubeR(bool clockWise);
	void rotateCubeU(bool clockWise);
	void rotateCubeD(bool clockWise);

}
#endif