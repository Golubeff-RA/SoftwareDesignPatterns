#pragma once
#include "drawer/idrawer.h"

class DefaultDrawer : public IDrawer {
public:
    void DrawLine(ImDrawList* draw_list, ImVec2 start, ImVec2 end) const override {
        draw_list->AddLine(start, end, IM_COL32(255, 255, 255, 255), 1.0f);
    }
    void DrawText(ImDrawList* draw_list, ImVec2 pos, const char* value) const override {
        draw_list->AddText(pos, IM_COL32(255, 255, 255, 255), value);
    }
};