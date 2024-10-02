#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

#include <iostream>

#include "stb_image.h"

class Texture {
public:
	unsigned int ID;

	Texture();

	void LoadRGB(const char* fileName);
	void LoadRGBA(const char* fileName);
	void Flip(bool value);
	void Activate(GLenum texture);
};
#endif