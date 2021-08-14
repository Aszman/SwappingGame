#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	GLuint ID;

	Shader(const char*, const char*);

	~Shader();

	void use()const;

	void setBool(const std::string&, bool) const;
	void setInt(const std::string&, int) const;
	void setFloat(const std::string&, float) const;

	void set2Float(const std::string&, glm::vec2&) const;
	void set3Float(const std::string&, float, float, float) const;
	void set3Float(const std::string&, glm::vec3&) const;
	void set4Float(const std::string&, float, float, float, float) const;

	void setMat3(const std::string&, const glm::mat3&) const;
	void setMat4(const std::string&, const glm::mat4&) const;

	void terminate();

private:
	void checkCompileErrors(unsigned int, std::string);

};

#endif