#pragma once
#include <imgui.h>
#include <memory>

class IDrawer {
public:
    virtual void DrawLine(ImDrawList* draw_list, ImVec2 start, ImVec2 end) const = 0;
    virtual void DrawText(ImDrawList* draw_list, ImVec2 pos, const char* value) const = 0;
    virtual ~IDrawer() = default;
};

using DrawerPtr = std::shared_ptr<IDrawer>;