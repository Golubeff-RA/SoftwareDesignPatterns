#pragma once

#include <drawer/default_drawer.h>

class LazyDrawer : public DefaultDrawer {
public:
    LazyDrawer(ImDrawList* draw_list, std::ostream& out, ImVec2 init_pos)
        : DefaultDrawer(draw_list, out, init_pos) {}
    void DrawLine(ImVec2, ImVec2) override {}
    void DrawBorder(char) override {}
};