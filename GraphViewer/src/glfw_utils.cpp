#include "glfw_utils.h"

#include <iostream>

void glfw_error_callback(int error_code, const char* description)
{
    if (error_code != GLFW_NO_ERROR) {
        std::cerr << "glfw_error_callback() code:" << error_code << " description:" << description << std::endl;
    }
}

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}