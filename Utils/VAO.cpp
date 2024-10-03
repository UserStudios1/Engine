#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

// CONTAINS POSITION LINKING
void VAO::Link1(VBO& VBO, GLuint index) {
	VBO.Bind();
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(index);
	VBO.Unbind();
}

// CONTAINS NORMAL LINKING
void VAO::Link2(VBO& VBO, GLuint index) {
	VBO.Bind();
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(index);
	VBO.Unbind();
}

void VAO::Bind() {
	glBindVertexArray(ID);
}

void VAO::Unbind() {
	glBindVertexArray(0);
}

void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
}