#include "Texture.h"

Texture::Texture() {
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	// texture wrapping/filter options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::LoadRGB(const char* fileName) {
	int width, height, nrChannels;
	unsigned char* data = stbi_load(fileName, &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load Texture (" << fileName << ")" << std::endl;
	}
	stbi_image_free(data);
}

void Texture::LoadRGBA(const char* fileName) {
	int width, height, nrChannels;
	unsigned char* data = stbi_load(fileName, &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load Texture (" << fileName << ")" << std::endl;
	}
	stbi_image_free(data);
}

void Texture::Flip(bool value) {
	stbi_set_flip_vertically_on_load(value);
}

void Texture::Activate(GLenum texture) {
	glActiveTexture(texture);
	glBindTexture(GL_TEXTURE_2D, ID);
}