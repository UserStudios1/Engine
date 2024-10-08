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
#include "Camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = 400.0f;
float lastY = 300.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	std::cout << "GLFW initialized." << std::endl;

	// GLAD init
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD." << std::endl;
		return -1;
	}
	std::cout << "GLAD initialized." << std::endl;

	// set Viewport
	glViewport(0, 0, 800, 600);
	// enabling default OpenGL Depth Test
	glEnable(GL_DEPTH_TEST);

	std::cout << "Initialization done.\n" << std::endl;

	// creating Shaders
	Shader lightningShader("Shader/lightningVertexShader.v", "Shader/lightningFragmentShader.f");
	Shader cubeShader("Shader/cubeVertexShader.v", "Shader/cubeFragmentShader.f");

	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	// buffers
	VAO cubeVAO;
	VAO lightCubeVAO;
	VBO VBO(vertices, sizeof(vertices));

	// linking cubeVAO buffer to VBO
	cubeVAO.Bind();
	cubeVAO.LinkPosition(0);
	cubeVAO.LinkNormals(1);
	cubeVAO.LinkTexture(2);

	// same with lightCubeVAO
	lightCubeVAO.Bind();
	lightCubeVAO.LinkPosition(0);	

	Texture diffuseMap, specularMap;
	diffuseMap.Load("wooden_container2.png");
	specularMap.Load("wooden_container2_specular.png");

	lightningShader.use();
	lightningShader.setInt("material.diffuse", 0);
	lightningShader.setInt("material.specular", 1);

	std::cout << "\nStarting Render Loop." << std::endl;

	while (!glfwWindowShouldClose(window)) {
		// frame rate logic
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		process_input(window);

		// render loop
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// lightning Shader settings
		lightningShader.use();
		// moving around point light
		lightningShader.setVec3("viewPos", camera.Position);
		lightningShader.setFloat("material.shininess", 32.0f);
		lightningShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		lightningShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		lightningShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		lightningShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
		// point light 1
		lightningShader.setVec3("pointLights[0].position", pointLightPositions[0]);
		lightningShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		lightningShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		lightningShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		lightningShader.setFloat("pointLights[0].constant", 1.0f);
		lightningShader.setFloat("pointLights[0].linear", 0.09f);
		lightningShader.setFloat("pointLights[0].quadratic", 0.032f);
		// point light 2
		lightningShader.setVec3("pointLights[1].position", pointLightPositions[1]);
		lightningShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		lightningShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		lightningShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		lightningShader.setFloat("pointLights[1].constant", 1.0f);
		lightningShader.setFloat("pointLights[1].linear", 0.09f);
		lightningShader.setFloat("pointLights[1].quadratic", 0.032f);
		// point light 3
		lightningShader.setVec3("pointLights[2].position", pointLightPositions[2]);
		lightningShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		lightningShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
		lightningShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		lightningShader.setFloat("pointLights[2].constant", 1.0f);
		lightningShader.setFloat("pointLights[2].linear", 0.09f);
		lightningShader.setFloat("pointLights[2].quadratic", 0.032f);
		// point light 4
		lightningShader.setVec3("pointLights[3].position", pointLightPositions[3]);
		lightningShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		lightningShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		lightningShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		lightningShader.setFloat("pointLights[3].constant", 1.0f);
		lightningShader.setFloat("pointLights[3].linear", 0.09f);
		lightningShader.setFloat("pointLights[3].quadratic", 0.032f);
		// spotLight
		lightningShader.setVec3("spotLight.position", camera.Position);
		lightningShader.setVec3("spotLight.direction", camera.Front);
		lightningShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		lightningShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		lightningShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		lightningShader.setFloat("spotLight.constant", 1.0f);
		lightningShader.setFloat("spotLight.linear", 0.09f);
		lightningShader.setFloat("spotLight.quadratic", 0.032f);
		lightningShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		lightningShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

		// transformation shit
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		lightningShader.setMat4("projection", projection);
		lightningShader.setMat4("view", view);

		glm::mat4 model = glm::mat4(1.0f);
		lightningShader.setMat4("model", model);

		diffuseMap.Activate(GL_TEXTURE0);
		specularMap.Activate(GL_TEXTURE1);

		// drawing cube
		/*cubeVAO.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);*/

		cubeVAO.Bind();
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			lightningShader.setMat4("model", model);
			
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		cubeVAO.Unbind();

		// cube shader settings for Point Light
		cubeShader.use();
		cubeShader.setMat4("projection", projection);
		cubeShader.setMat4("view", view);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		cubeShader.setMat4("model", model);

		// drawing light cube (light source)
		/*lightCubeVAO.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		lightCubeVAO.Unbind();*/

		lightCubeVAO.Bind();
		for (int i = 0; i < 4; i++) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f));
			cubeShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		lightCubeVAO.Unbind();

		// swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// clean up
	std::cout << "Render Loop finished.\nBeginning Clean up." << std::endl;
	glfwTerminate();
	lightCubeVAO.Delete();
	cubeVAO.Delete();
	VBO.Delete();
	cubeShader.Delete();
	lightningShader.Delete();
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

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.ProcessKeyboard(LEFT, deltaTime);;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.ProcessKeyboard(RIGHT, deltaTime);;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}