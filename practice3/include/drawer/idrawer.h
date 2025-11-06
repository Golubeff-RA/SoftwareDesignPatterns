#pragma once
#include <imgui.h>

#include <memory>

class IDrawer {
public:
    virtual void DrawLine(ImVec2 start, ImVec2 end) = 0;
    virtual void DrawLine(char sym) = 0;
    virtual void DrawText(ImVec2 pos, const char* value) = 0;
    virtual void DrawText(const char* value) = 0;
    virtual ~IDrawer() = default;
};

using DrawerPtr = std::shared_ptr<IDrawer>;