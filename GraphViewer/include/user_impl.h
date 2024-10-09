#ifndef USER_IMPL_H
#define USER_IMPL_H

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

void user_glfw_error_callback(int error_code, const char* description);
void user_glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void user_glfw_drop_callback(GLFWwindow* window, int path_count, const char* paths[]);
void user_glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void user_imgui_render();

#endif