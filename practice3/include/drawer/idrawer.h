#pragma once
#include <imgui.h>
#include <memory>

class IDrawer {
public:
    virtual ImVec2 GetPos() const = 0;
    virtual void DrawLine(ImVec2 start, ImVec2 end) = 0;
    virtual void DrawText(ImVec2 pos, const char* value) = 0;
    virtual void DrawText(const char* value) = 0;
    virtual void DrawBorder(char sym) = 0;
    virtual ~IDrawer() = default;
};

using DrawerPtr = std::shared_ptr<IDrawer>;