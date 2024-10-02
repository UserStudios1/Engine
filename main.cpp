#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Shader/Shader.h"
#include "Utils/VBO.h"
#include "Utils/VAO.h"
#include "Utils/EBO.h"
#include "Utils/Texture.h"
#include "Utils/stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

int main() {
	// GLFW init
	std::cout << "Starting Initialization." << std::endl;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Engine", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	std::cout << "GLFW initialized." << std::endl;

	// GLAD init
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD." << std::endl;
		return -1;
	}
	std::cout << "GLAD initialized." << std::endl;

	// set Viewport
	glViewport(0, 0, 800, 600);

	std::cout << "Initialization done.\n" << std::endl;

	float vertices[] = {
		// position          // texture
		 0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,  0.0f, 1.0f
	};
	unsigned int indices[]{
		0, 1, 3,
		1, 2, 3
	};

	// buffers
	VAO VAO;
	VBO VBO(vertices, sizeof(vertices));
	EBO EBO(indices, sizeof(indices));

	VAO.Bind();
	VAO.Link1(VBO, 0);
	VAO.Link2(VBO, 1);

	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();

	// shaders
	Shader Shader("Shader/vertexShader.v", "Shader/fragmentShader.f");

	// textures
	Texture Texture1;
	Texture1.LoadRGB("wooden_container.jpg");
	Texture1.Flip(false);

	Texture Texture2;
	Texture2.Flip(true);
	Texture2.LoadRGBA("awesomeface.png");

	Shader.use();
	Shader.setIntU1("texture1", 0);
	Shader.setIntU1("texture2", 1);

	

	std::cout << "\nStarting Render Loop." << std::endl;

	while (!glfwWindowShouldClose(window)) {
		// input
		process_input(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Texture1.Activate(GL_TEXTURE0);
		Texture2.Activate(GL_TEXTURE1);

		Shader.use();
		// transformation shit
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		unsigned int transformLoc = glGetUniformLocation(Shader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		VAO.Bind();
		EBO.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// WIREFRAME MODE
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		// swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// clean up
	std::cout << "Render Loop finished.\nBeginning Clean up." << std::endl;
	glfwTerminate();
	VAO.Delete();
	VBO.Delete();
	EBO.Delete();
	Shader.Delete();
	std::cout << "Clean up finished." << std::endl;
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}