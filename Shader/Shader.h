#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);

	void use();
	void Delete();
	void setBoolU1(const std::string& name, bool value) const;
	void setIntU1(const std::string& name, int value) const;
	void setFloatU1(const std::string& name, float value) const;
	void setBoolU2(const std::string& name, bool value1, bool value2) const;
	void setIntU2(const std::string& name, int value1, int value2) const;
	void setFloatU2(const std::string& name, float value1, float value2) const;
	void setBoolU3(const std::string& name, bool value1, bool value2, bool value3) const;
	void setIntU3(const std::string& name, int value1, int value2, int value3) const;
	void setFloatU3(const std::string& name, float value1, float value2, float value3) const;
	void setBoolU4(const std::string& name, bool value1, bool value2, bool value3, bool value4) const;
	void setIntU4(const std::string& name, int value1, int value2, int value3, int value4) const;
	void setFloatU4(const std::string& name, float value1, float value2, float value3, float value4) const;
};

#endif