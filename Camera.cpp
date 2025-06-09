#include "Camera.h"



Camera::Camera() {
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);//相机位置
	cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);//相机目标位置,即定义的相机一开始指向的点,只定义为方向,,定义为0,0,0也行
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);//相机的正上方定义,在右手坐标系里,y轴通常指上,所以应当定义y轴正方向为上,否则不符合正常思维
	LastX = 400;
	LastY = 300;
	first = true;
	pitch = yaw = 0.0f;
	lastFrame = glfwGetTime();
}

void Camera::DealMove(GLFWwindow* window) {
	nowFrame = glfwGetTime();
	float deltaTime = nowFrame - lastFrame;
	lastFrame = nowFrame;
	cameraSpeed = 2.5f * deltaTime;
	if (isQuicked)cameraSpeed = cameraSpeed * 4.0f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	//cameraPos.y = 0.0f;
}

void Camera::DealRotate(GLFWwindow* window,float xpos,float ypos) {
	if (first) // 这个bool变量初始时是设定为true的
	{
		LastX = xpos;
		LastY = ypos;
		first = false;
	}

	float xoffset = xpos - LastX;
	float yoffset = LastY - ypos; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
	LastX = xpos;
	LastY = ypos;

	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	pitch += yoffset;
	yaw += xoffset;
	if (pitch > 360.f)pitch = 0.0f;
	if (yaw > 360.0f)yaw = 0.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);
}


glm::mat4 Camera::LookAt(){
	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 rotate = glm::mat4(1.0f);
	glm::vec3 z = glm::normalize(-cameraFront);
	glm::vec3 x = glm::normalize(glm::cross(cameraUp, z));
	glm::vec3 y = glm::normalize(glm::cross(z, x));
	for (int i = 0; i < 3; i++) {
		rotate[i][0] = x[i];
		rotate[i][1] = y[i];
		rotate[i][2] = z[i];
		trans[3][i] = -cameraPos[i];
	}
	glm::mat4 ModelView = glm::mat4(1.0f);
	ModelView = rotate * trans;
	return ModelView;
}