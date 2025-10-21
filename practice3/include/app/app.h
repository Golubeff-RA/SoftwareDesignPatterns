#pragma once

#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

#include <functional>
#include <string>

class App {
public:
    App(int width = 1280, int height = 720, const std::string& title = "ImGUI Application");
    ~App();

    int Run();
    void SetRenderCallback(std::function<void()> callback) { m_renderCallback = callback; }
    void SetClearColor(float r, float g, float b, float a = 1.0f);

private:
    bool InitGLFW();
    bool InitImGUI();

    void MainLoop();
    void Cleanup();

    GLFWwindow* m_window;
    int m_width;
    int m_height;
    std::string m_title;
    ImVec4 m_clearColor;
    std::function<void()> m_renderCallback;

    float m_fps;
    int m_frameCount;
    double m_lastTime;
};