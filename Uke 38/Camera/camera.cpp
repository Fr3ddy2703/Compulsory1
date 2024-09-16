#include "pch.h"
#include "camera.h"
#include "../Shaders/shader.h"

void camera::initCamera()
{
    viewLoc = glGetUniformLocation(Shader::ShaderProgram, "view");
    projectionLoc = glGetUniformLocation(Shader::ShaderProgram, "projection");
}

glm::mat4 camera::getView()
{
    glm::mat4 view = glm::mat4(1.f);
    view = glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);
    return view;
}

glm::mat4 camera::getProjection(float width, float height)
{
    glm::mat4 proj = glm::mat4(1.f);
    proj = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
    return proj;
}