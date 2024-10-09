#include "user_impl.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

void user_glfw_error_callback(int error_code, const char* description)
{

}
void user_glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}
void user_glfw_drop_callback(GLFWwindow* window, int path_count, const char* paths[])
{

}
void user_glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

}

void user_imgui_render()
{
    // Create a fullscreen window
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::Begin("Fullscreen Window", nullptr,
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoCollapse);

    // Your ImGui content goes here
    ImGui::Text("Hello, world!");

    ImGui::End();
}