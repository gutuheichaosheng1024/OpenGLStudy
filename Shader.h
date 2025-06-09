#pragma once

#include<string>
#include<unordered_map>
#include "vendor/glm/mat4x4.hpp"


class Shader {
public:
	std::string ShaderName;
	unsigned int m_RenderID;
	std::unordered_map<std::string, int>uniformPos;

	Shader(std::string& _filePathv, std::string& _filePathf);
	Shader(std::string& _filePathv,std::string& _filePathg ,std::string& _filePathf);
	std::string GetShaderSource(std::string& _filePath);
	void GenerateShader(int type, std::string& _filePath);
	~Shader();
	void Use();
	void GiveUp();
	unsigned int GetUnifromPosition(const std::string& UniformName);
	void SetUniform1i(const std::string& UniformName,int value);
	void SetUniform1f(const std::string& UniformName, float value);
	void SetUniformMatrix4fv(const std::string& UniformName,glm::mat4 matrix);
	void SetUniformMatrix3fv(const std::string& UniformName, glm::mat3 matrix);
	void SetUniformVector3fv(const std::string& UniformName, glm::vec3 vector);
	void SetUniformVector2fv(const std::string& UniformName, glm::vec2 vector);
};


