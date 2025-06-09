#include "Shader.h"
#include<fstream>
#include<sstream>
#include<iostream>
#include<GL/glew.h>
#include "vendor/glm/gtc/type_ptr.hpp"



Shader::Shader(std::string& _filePathv, std::string& _filePathf) {
	m_RenderID = glCreateProgram();
	GenerateShader(1, _filePathv);
	GenerateShader(3, _filePathf);
	glLinkProgram(m_RenderID);
}


Shader::Shader(std::string& _filePathv, std::string& _filePathg, std::string& _filePathf) {
	m_RenderID = glCreateProgram();
	GenerateShader(1, _filePathv);
	GenerateShader(2, _filePathg);
	GenerateShader(3, _filePathf);
	glLinkProgram(m_RenderID);
}


Shader::~Shader() {
	glDeleteProgram(m_RenderID);
}
void Shader::Use() {
	glUseProgram(m_RenderID);
}
void Shader::GiveUp() {
	glUseProgram(0);
}


std::string Shader::GetShaderSource(std::string& _filePath) {
	std::ifstream ifs;
	ifs.open(_filePath);
	std::stringstream sstream;
	std::string line;

	while (getline(ifs, line))
	{
		sstream << line << '\n';
	}

	std::string source = sstream.str();

	return source;
}

void Shader::GenerateShader(int type, std::string& _filePath) {
	unsigned int id;
	if (type == 1) {
		id = glCreateShader(GL_VERTEX_SHADER);
	}
	else if(type == 2){
		id = glCreateShader(GL_GEOMETRY_SHADER);
	}
	else {
		id = glCreateShader(GL_FRAGMENT_SHADER);
	}
	std::string Ssourcev = GetShaderSource(_filePath);
	const char* sourcev = Ssourcev.c_str();
	glShaderSource(id, 1, &sourcev, nullptr);
	glCompileShader(id);


	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "fail to compile  " << id << "  shader" << std::endl;
		std::cout << message << std::endl;
	}

	glAttachShader(m_RenderID, id);
	glDeleteShader(id);
}

unsigned int Shader::GetUnifromPosition(const std::string& UniformName) {
	if (uniformPos.find(UniformName) != uniformPos.end())return uniformPos[UniformName];
	int pos = glGetUniformLocation(m_RenderID, UniformName.c_str());
	if (pos == -1) {
		std::cout <<UniformName << "  is a Wrong Name" << std::endl;
	}
	else {
		uniformPos[UniformName] = pos;
	}
	return pos;
}


void Shader::SetUniform1i(const std::string& UniformName, int value) {
	unsigned int pos = GetUnifromPosition(UniformName);
	glUniform1i(pos, value);
}


void Shader::SetUniform1f(const std::string& UniformName, float value) {
	unsigned int pos = GetUnifromPosition(UniformName);
	glUniform1f(pos, value);
}

void Shader::SetUniformMatrix4fv(const std::string& UniformName, glm::mat4 matrix) {
	unsigned int pos = GetUnifromPosition(UniformName);
	glUniformMatrix4fv(pos, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetUniformVector3fv(const std::string& UniformName, glm::vec3 vector) {
	unsigned int pos = GetUnifromPosition(UniformName);
	glUniform3fv(pos, 1, glm::value_ptr(vector));
}


void Shader::SetUniformVector2fv(const std::string & UniformName, glm::vec2 vector) {
	unsigned int pos = GetUnifromPosition(UniformName);
	glUniform2fv(pos, 1, glm::value_ptr(vector));
}

void Shader::SetUniformMatrix3fv(const std::string& UniformName, glm::mat3 matrix) {
	unsigned int pos = GetUnifromPosition(UniformName);
	glUniformMatrix3fv(pos, 1,GL_FALSE ,glm::value_ptr(matrix));
}