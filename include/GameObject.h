#pragma once

#include <glm.hpp>

class GameObject
{
public:
    /* Creates an empty gameobject. */
    GameObject();

    /* Creates a gameobject */
    //GameObject();

private:
    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};