#include "glfw_utils.h"

#include "glh/glh.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include <iostream>

const uint32_t DEFAULT_WINDOW_WIDTH = 800;
const uint32_t DEFAULT_WINDOW_HEIGHT = 600;
const char* DEFAULT_WINDOW_NAME = "GraphViewer";

int main()
{
    if (!glfwInit()) {
        std::cerr << "ERROR glfwInit()" << std::endl;
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    GLFWwindow* window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_NAME, nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "ERROR glfwCreateWindow()" << std::endl;
        return EXIT_FAILURE;
    }

    glfwSetErrorCallback(glfw_error_callback);
    glfwSetKeyCallback(window, glfw_key_callback);

    glfwMakeContextCurrent(window);

    if (!glh::utils::loadExtensions(glfwGetProcAddress)) {
        std::cerr << "ERROR glh::utils::loadExtensions()" << std::endl;
        return EXIT_FAILURE;
    }

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();



        glfwSwapBuffers(window);
    }

    return EXIT_SUCCESS;
}