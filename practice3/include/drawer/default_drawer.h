#pragma once
#include "drawer/idrawer.h"

class DefaultDrawer : public IDrawer {
public:
    DefaultDrawer(ImDrawList* draw_list, std::ostream& out, ImVec2 init_pos)
        : draw_list_(draw_list), out_(out), init_pos_(init_pos) {}

    void DrawLine(ImVec2 start, ImVec2 end) override {
        start.x += init_pos_.x;
        start.y += init_pos_.y;
        end.x += init_pos_.x;
        end.y += init_pos_.y;
        this->draw_list_->AddLine(start, end, IM_COL32(255, 255, 255, 255),
                                  1.0f);
    }
    void DrawText(ImVec2 pos, const char* value) override {
        pos.x += init_pos_.x;
        pos.y += init_pos_.y;
        this->draw_list_->AddText(pos, IM_COL32(255, 255, 255, 255), value);
    }

    void DrawText(const char* value) override { this->out_ << value; }

    void DrawLine(char sym) override { this->out_ << sym; }

private:
    ImDrawList* draw_list_;
    std::ostream& out_;
    ImVec2 init_pos_;
};