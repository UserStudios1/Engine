#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

void VAO::Link(VBO& VBO, GLuint index) {
	VBO.Bind();
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(index);
	VBO.Unbind();
}

// USE LINK1, LINK2, LINK3 FOR RECTANGLE
// CONTAINS POSITION LINKING
void VAO::Link1(VBO& VBO, GLuint index) {
	VBO.Bind();
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(index);
	VBO.Unbind();
}

// CONTAINS COLOR LINKING
void VAO::Link2(VBO& VBO, GLuint index) {
	VBO.Bind();
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(index);
	VBO.Unbind();
}

// CONTAINS TEXTURE LINKING
void VAO::Link3(VBO& VBO, GLuint index) {
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