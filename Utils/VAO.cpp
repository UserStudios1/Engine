#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

// CONTAINS POSITION LINKING
void VAO::LinkPosition(VBO& VBO, GLuint index) {
	VBO.Bind();
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(index);
	VBO.Unbind();
}

// CONTAINS NORMAL LINKING
void VAO::LinkNormals(VBO& VBO, GLuint index) {
	VBO.Bind();
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(index);
	VBO.Unbind();
}

// CONTAINS TEXTURE LINKING
void VAO::LinkTexture(VBO& VBO, GLuint index) {
	VBO.Bind();
	glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
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