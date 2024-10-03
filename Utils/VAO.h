#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>

#include "VBO.h"

class VAO {
public:
	unsigned int ID;

	VAO();

	void LinkPosition(VBO& VBO, GLuint index);
	void LinkNormals(VBO& VBO, GLuint index);
	void LinkTexture(VBO& VBO, GLuint index);
	void Bind();
	void Unbind();
	void Delete();
};
#endif