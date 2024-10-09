#ifndef GLFW_UTILS_H
#define GLFW_UTILS_H

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

void glfw_error_callback(int error_code, const char* description);
void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif