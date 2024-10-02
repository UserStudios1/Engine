#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

class EBO {
public:
	unsigned int ID;

	EBO(GLuint* indices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};
#endif