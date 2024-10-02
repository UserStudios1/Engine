#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>

#include "VBO.h"

class VAO {
public:
	unsigned int ID;

	VAO();

	void Link1(VBO& VBO, GLuint index);
	void Link2(VBO& VBO, GLuint index);
	void Bind();
	void Unbind();
	void Delete();
};
#endif