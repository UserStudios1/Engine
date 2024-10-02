#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "Shader file not successfully read." << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "Vertex Shader Compilation failed.\nReason: " << infoLog << std::endl;
	}
	else {
		std::cout << "Vertex Shader Compilation successfull." << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "Fragment Shader Compilation failed.\nReason: " << infoLog << std::endl;
	}
	else {
		std::cout << "Fragment Shader Compilation successfull." << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "Shader Program Linking failed.\nReason: " << infoLog << std::endl;
	}
	else {
		std::cout << "Shader Program Linking successfull." << std::endl;
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
}


void Shader::use() {
	glUseProgram(ID);
}

void Shader::Delete() {
	glDeleteProgram(ID);
}

void Shader::setBoolU1(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setIntU1(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloatU1(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setBoolU2(const std::string& name, bool value1, bool value2) const
{
	glUniform2i(glGetUniformLocation(ID, name.c_str()), (int)value1, (int)value2);
}
void Shader::setIntU2(const std::string& name, int value1, int value2) const
{
	glUniform2i(glGetUniformLocation(ID, name.c_str()), value1, value2);
}
void Shader::setFloatU2(const std::string& name, float value1, float value2) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), value1, value2);
}
void Shader::setBoolU3(const std::string& name, bool value1, bool value2, bool value3) const
{
	glUniform3i(glGetUniformLocation(ID, name.c_str()), (int)value1, (int)value2, (int)value3);
}
void Shader::setIntU3(const std::string& name, int value1, int value2, int value3) const
{
	glUniform3i(glGetUniformLocation(ID, name.c_str()), value1, value2, value3);
}
void Shader::setFloatU3(const std::string& name, float value1, float value2, float value3) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3);
}
void Shader::setBoolU4(const std::string& name, bool value1, bool value2, bool value3, bool value4) const
{
	glUniform4i(glGetUniformLocation(ID, name.c_str()), (int)value1, (int)value2, (int)value3, (int)value4);
}
void Shader::setIntU4(const std::string& name, int value1, int value2, int value3, int value4) const
{
	glUniform4i(glGetUniformLocation(ID, name.c_str()), value1, value2, value3, value4);
}
void Shader::setFloatU4(const std::string& name, float value1, float value2, float value3, float value4) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3, value4);
}