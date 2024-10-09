#include "user_impl.h"

#include "imgui.h"
#include "implot.h"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

std::vector<std::vector<double>> graphs;

std::vector<double> readCSVToVector(const std::string& filename) {
    std::vector<double> values;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return values;
    }

    while (std::getline(file, line)) {
        // Remove any trailing comma and whitespace
        line.erase(line.find_last_not_of(", \n\r\t") + 1);

        if (!line.empty()) {
            try {
                double value = std::stod(line);
                values.push_back(value);
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Invalid number format: " << line << std::endl;
            }
            catch (const std::out_of_range& e) {
                std::cerr << "Number out of range: " << line << std::endl;
            }
        }
    }

    file.close();
    return values;
}

void user_glfw_error_callback(int error_code, const char* description)
{

}
void user_glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}
void user_glfw_drop_callback(GLFWwindow* window, int path_count, const char* paths[])
{
    for (int i = 0; i < path_count; i++) {
        std::vector<double> graph = readCSVToVector(paths[i]);
        graphs.push_back(graph);
    }
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
    ImGui::Begin("Graph Viewer", nullptr,
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoCollapse);

    uint32_t idCount = 0;
    for (std::vector<double> graph : graphs) {
        ImGui::PushID(idCount++);
        if (ImPlot::BeginPlot("##NoTitle")) {
            ImPlot::PlotLine("Data", graph.data(), graph.size());
            ImPlot::EndPlot();
        }
        ImGui::PopID();
    }


    ImGui::End();
}