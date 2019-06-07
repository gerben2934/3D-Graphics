/*
	Engine functionality
*/
#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <GL\freeglut.h>
#include "Globals.hpp"
#include "Game.hpp"
#include "ObjectModel.h"
#include <math.h>

#define APP_NAME "Game"
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

using namespace std;

//up 0 --> white
//down 1 --> yellow
//left 2 --> green
//right 3 --> blue
//front 4 --> red 
//back 5 --> orange

struct Camera
{
	float posX = 0;
	float posY = 0;
	float rotX = 0;
	float rotY = 0;
	float posZ = 0;
	float rotZ = 0;
} camera;

//-----------------------------
//			Variables
//-----------------------------
bool keys[256];
bool skeys[5]; //for arrow keys

int windowWidth = WINDOW_WIDTH;
int windowHeight = WINDOW_HEIGHT;
GLuint texturePack;
const char* textureFilename = "texturePack.png";

void reshape(int w, int h)
{
	windowWidth = w;
	windowHeight = h;
	glViewport(0, 0, w, h);
}

void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, windowWidth / (float)windowHeight, 0.1f, 50.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glRotatef(camera.rotZ, 0, 0, 1);
	glTranslatef(camera.posX, camera.posY, camera.posZ);

	Game::draw();

	glutSwapBuffers();
	glClear(GL_DEPTH_BUFFER_BIT);
}

int lastTime = 0;

void move(float angle, float fac)
{
	camera.posX += (float)cos((camera.rotY + angle) / 180 * M_PI) * fac;
	camera.posY += (float)sin((camera.rotY + angle) / 180 * M_PI) * fac;
}

void idle() {
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;

	const float speed = 3;

	//glutWarpPointer(windowWidth / 2, windowHeight / 2);

	if (skeys[0] && skeys[4]) {
		camera.posY -= 0.1;
	}
	else if (skeys[1] && skeys[4]) {
		//if (camera.posY < 0) {
			camera.posY += 0.1;
		//}
	}

	else if (skeys[0]) {
		//cout << "\r\nUP arrow key";
		camera.posZ += 0.1;
	}
	else if (skeys[1]) {
		//cout << "\r\nDOWN arrow key";
		camera.posZ -= 0.1;
	}
	else if (skeys[2]) {
		camera.posX += 0.1;
		//cout << "\r\nLEFT arrow key";
	}
	else if (skeys[3]) {
		camera.posX -= 0.1;
		//cout << "\r\nRIGHT arrow key";
	}
	Game::update(deltaTime);
	glutPostRedisplay();
}

bool justMovedMouse = false;
void mousePassiveMotion(int x, int y)
{
	int dx = x - windowWidth / 2;
	int dy = y - windowHeight / 2;
	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400 && !justMovedMouse)
	{
		camera.rotY += dx / 10.0f;
		camera.rotX += dy / 10.0f;
	}
	if (!justMovedMouse)
	{
		glutWarpPointer(windowWidth / 2, windowHeight / 2);
		justMovedMouse = true;
	}
	else
		justMovedMouse = false;
}

void keyboard(unsigned char key, int x, int  y) {
	keys[key] = true;

	if (key == 27)
		exit(0);
	//up 0
	cout << "\r\nKey: " << key;
	if (keys['u']) {
		cout << "\r\nup anticlockwise";
		//Game::rotateCubeU(false);
	}
	if (keys['U']) {
		cout << "\r\nUp clockwise";
		//Game::rotateCubeU(true);
	}

	//down 1
	if (keys['d']) {
		cout << "\r\ndown anticlockwise";
		//Game::rotateCubeD(false);
	}
	if (keys['D']) {
		cout << "\r\nDown clockwise";
		//Game::rotateCubeD(true);
	}

	//left 2
	if (keys['l']) {
		cout << "\r\nleft anticlockwise";
		//Game::rotateCubeL(false);
	}
	if (keys['L']) {
		cout << "\r\nLeft clockwise";
		//Game::rotateCubeL(true);
	}

	//right 3
	if (keys['r']) {
		cout << "\r\nright anticlockwise";
		Game::rotateCubeR(false);
	}
	if (keys['R']) {
		cout << "\r\nRight clockwise";
		Game::rotateCubeR(true);
	}

	//front 4
	if (keys['f']) {
		cout << "\r\nfront anticlockwise";
		Game::rotateCubeF(false);
	}
	if (keys['F']) {
		cout << "\r\nFront clockwise";
		Game::rotateCubeF(true);

	}

	//back 5
	if (keys['b']) {
		cout << "\r\nback anticlockwise";
		Game::rotateCubeB(false);
	}
	if (keys['B']) {
		cout << "\r\nBack clockwise";
		Game::rotateCubeB(true);
	}

	//cout << "Key: " << key << std::endl;
}

void keyboardup(unsigned char key, int x, int y) {
	keys[key] = false;
}

void specialKeys(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		skeys[0] = true;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		skeys[1] = true;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		skeys[2] = true;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		skeys[3] = true;
		glutPostRedisplay();
	case (GLUT_KEY_CTRL_L):
		skeys[4] = true;
		glutPostRedisplay();
	}
	//std::cout << "Special key: " << key << std::endl;
}

void specialKeysUp(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		skeys[0] = false;
		break;
	case GLUT_KEY_DOWN:
		skeys[1] = false;
		break;
	case GLUT_KEY_LEFT:
		skeys[2] = false;
		break;
	case GLUT_KEY_RIGHT:
		skeys[3] = false;
		break;
	case (GLUT_KEY_CTRL_L):
		skeys[4] = false;
		break;
	}
}

bool initGlut(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInit(&argc, argv);
	glutCreateWindow(APP_NAME);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);

	//Regular keys:
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardup);
	//Special keys:
	glutSpecialFunc(specialKeys);
	glutSpecialUpFunc(specialKeysUp);

	glutPassiveMotionFunc(mousePassiveMotion);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	return true;
}

bool initOpenGL()
{
	glEnable(GL_DEPTH_TEST);
	return true;
}
int main(int argc, char** argv)
{
	windowWidth = WINDOW_WIDTH;
	windowHeight = WINDOW_HEIGHT;

	if (initGlut(argc, argv))
		std::cout << "\r\nSuccesfully initialized glut.\n";
	else
	{
		std::cout << "\r\nFailed initializing glut.\n";
		return GLUT_INIT_FAILED;
	}

	if (initOpenGL())
		cout << "\r\nSuccesfully initialized OpenGL.\n";
	else
	{
		cout << "\r\nFailed initializing OpenGL.\n";
		return OPENGL_INIT_FAILED;
	}
	glEnable(GL_DEPTH_TEST);

	Texture texture = Texture(textureFilename);
	texture.loadTextureFromFile(textureFilename);
	texturePack = texture.getTextureId();

	// Start loading in game content.
	Game::loadContent();
	Game::onResize(windowWidth, windowHeight);
	// Start game.
	glutMainLoop();
	Game::onClose();

	return EXIT_SUCCESS;
}