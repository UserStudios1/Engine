#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

// CONTAINS POSITION LINKING
void VAO::LinkPosition(GLuint index) {
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(index);
}

// CONTAINS NORMAL LINKING
void VAO::LinkNormals(GLuint index) {
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(index);
}

// CONTAINS TEXTURE LINKING
void VAO::LinkTexture(GLuint index) {
	glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(index);
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