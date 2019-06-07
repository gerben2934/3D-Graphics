#pragma once

#include <string>
#include <vector>
#include <list>

#include <windows.h>
#include <gl/GL.h>
//#include "Vec.h"
class Texture
{
public:
	Texture(const std::string &dirName);
	const std::string dirName;
	GLuint getTextureId();
	GLuint textureId;

	void loadTextureFromFile(const char *filename);
};