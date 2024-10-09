#include "user_impl.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glh/glh.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

#include <windows.h>
#include <dwmapi.h>

#include <iostream>

const uint32_t DEFAULT_WINDOW_WIDTH = 800;
const uint32_t DEFAULT_WINDOW_HEIGHT = 600;
const char* DEFAULT_WINDOW_NAME = "GraphViewer";

void glfw_error_callback(int error_code, const char* description)
{
    if (error_code != GLFW_NO_ERROR) {
        std::cerr << "glfw_error_callback() code:" << error_code << " description:" << description << std::endl;
    }

    user_glfw_error_callback(error_code, description);
}

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    user_glfw_key_callback(window, key, scancode, action, mods);
}

void glfw_drop_callback(GLFWwindow* window, int path_count, const char* paths[])
{
    user_glfw_drop_callback(window, path_count, paths);
}

void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

    user_glfw_mouse_button_callback(window, button, action, mods);
}

int mainImpl()
{
    // GLFW INIT
    if (!glfwInit()) {
        std::cerr << "ERROR glfwInit()" << std::endl;
        return EXIT_FAILURE;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    //glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_NAME, nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "ERROR glfwCreateWindow()" << std::endl;
        return EXIT_FAILURE;
    }
    glfwSetErrorCallback(glfw_error_callback);
    glfwSetKeyCallback(window, glfw_key_callback);
    glfwSetDropCallback(window, glfw_drop_callback);
    glfwSetMouseButtonCallback(window, glfw_mouse_button_callback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    HWND hWnd = glfwGetWin32Window(window);
    BOOL value = TRUE;
    HRESULT hr = DwmSetWindowAttribute(hWnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &value, sizeof(value));

    // GLH EXTENSION INIT
    if (!glh::utils::loadExtensions(glfwGetProcAddress)) {
        std::cerr << "ERROR glh::utils::loadExtensions()" << std::endl;
        return EXIT_FAILURE;
    }

    // DEARIMGUI INIT
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    // MAIN LOOP
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        user_imgui_render();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    return EXIT_SUCCESS;
}

int main()
{
    return mainImpl();
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    return mainImpl();
}