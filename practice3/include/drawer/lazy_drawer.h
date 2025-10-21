#pragma once

#include <drawer/default_drawer.h>

class LazyDrawer: public DefaultDrawer {
public:
    void DrawLine(ImDrawList* draw_list, ImVec2 start, ImVec2 end) const override {
    }
};