#pragma once
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"
#include "vendor/glm/gtx/string_cast.hpp"
#include "GLFW/glfw3.h"


class Camera {
public:
	bool first;
	float LastX, LastY;
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	float pitch,yaw;
	float cameraSpeed,lastFrame,nowFrame;
	bool isQuicked;
	Camera();
	void DealMove(GLFWwindow* window);
	void DealRotate(GLFWwindow* window, float xpos, float ypos);
	glm::mat4 LookAt();
};
