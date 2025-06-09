#pragma once
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"


class DirLight {
public:
    glm::vec3 direction;
    glm:: vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};
