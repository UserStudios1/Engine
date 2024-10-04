#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>

#include "VBO.h"

class VAO {
public:
	unsigned int ID;

	VAO();

	void LinkPosition(GLuint index);
	void LinkNormals(GLuint index);
	void LinkTexture(GLuint index);
	void Bind();
	void Unbind();
	void Delete();
};
#endif