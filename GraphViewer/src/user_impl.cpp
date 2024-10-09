#include "user_impl.h"

#include "imgui.h"
#include "implot.h"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <unordered_map>

std::unordered_map<std::filesystem::path, std::vector<double>> graphs;

std::vector<double> readCSVToVector(const std::filesystem::path& path) {
    std::vector<double> values;
    std::ifstream file(path.c_str());
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << path.filename() << std::endl;
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
        std::filesystem::path path(paths[i]);
        if (path.extension() != ".csv") continue;
        if (graphs.find(path) != graphs.end()) continue;
        
        std::vector<double> graph = readCSVToVector(path);
        graphs.emplace(path, graph);
    }
}
void user_glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

}

void CenteredText(const char* text, ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f))
{
    float windowWidth = ImGui::GetWindowSize().x;
    float textWidth = ImGui::CalcTextSize(text).x;

    float windowHeight = ImGui::GetWindowSize().y;
    float textHeight = ImGui::CalcTextSize(text).y;

    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    ImGui::SetCursorPosY((windowHeight - textHeight) * 0.5f);

    ImGui::PushStyleColor(ImGuiCol_Text, color);
    ImGui::Text(text);
    ImGui::PopStyleColor();
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
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_AlwaysVerticalScrollbar);

    if (graphs.size() == 0) {
        CenteredText("Drop a CSV file into this window", ImVec4(0.5f, 0.5f, 0.5f, 0.5f));
    }
    else {
        uint32_t idCount = 0;
        for (std::pair<std::filesystem::path, std::vector<double>> graph : graphs) {
            ImGui::PushID(idCount++);
            if (ImPlot::BeginPlot(graph.first.filename().string().c_str())) {
                ImPlot::PlotLine("Data", graph.second.data(), graph.second.size());
                ImPlot::EndPlot();
            }
            ImGui::PopID();
        }
    }



    ImGui::End();
}