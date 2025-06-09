#pragma once

#include<iostream>
#include<vector>

class Texture {
public:
	unsigned int m_RenderID;
	std::string type;
	std::string path;
	Texture(const std::string& _filePath,bool useF);
	Texture(const std::vector<std::string>faces);
	void EnableTexture(int _type, unsigned int offset = 0);
};
