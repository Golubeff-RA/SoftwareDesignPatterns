#include "app/app.h"

#include <chrono>
#include <iostream>

void GLFWErrorCallback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

App::App(int width, int height, const std::string& title)
    : m_window(nullptr),
      m_width(width),
      m_height(height),
      m_title(title),
      m_clearColor(0.45f, 0.55f, 0.60f, 1.00f),
      m_fps(0.0f),
      m_frameCount(0),
      m_lastTime(0.0) {}

App::~App() { Cleanup(); }

bool App::InitGLFW() {
    glfwSetErrorCallback(GLFWErrorCallback);

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if (!m_window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    return true;
}

bool App::InitImGUI() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    if (!ImGui_ImplGlfw_InitForOpenGL(m_window, true)) {
        std::cerr << "Failed to initialize ImGUI GLFW backend" << std::endl;
        return false;
    }

    if (!ImGui_ImplOpenGL3_Init("#version 330")) {
        std::cerr << "Failed to initialize ImGUI OpenGL3 backend" << std::endl;
        return false;
    }

    return true;
}

void App::SetClearColor(float r, float g, float b, float a) { m_clearColor = ImVec4(r, g, b, a); }

int App::Run() {
    if (!InitGLFW()) {
        return -1;
    }

    if (!InitImGUI()) {
        return -1;
    }
    ImGuiIO& io = ImGui::GetIO();

    float scale_factor = 1.2f;
    ImGui::GetStyle().ScaleAllSizes(scale_factor);
    io.FontGlobalScale = scale_factor;

    MainLoop();
    return 0;
}

void App::MainLoop() {
    while (!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        m_renderCallback();
        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(m_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(m_clearColor.x * m_clearColor.w, m_clearColor.y * m_clearColor.w,
                     m_clearColor.z * m_clearColor.w, m_clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_window);

        m_frameCount++;
        double currentTime = glfwGetTime();
        if (currentTime - m_lastTime >= 1.0) {
            m_fps = static_cast<float>(m_frameCount / (currentTime - m_lastTime));
            m_frameCount = 0;
            m_lastTime = currentTime;
        }
    }
}

void App::Cleanup() {
    if (ImGui::GetCurrentContext()) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    if (m_window) {
        glfwDestroyWindow(m_window);
    }
    glfwTerminate();
}