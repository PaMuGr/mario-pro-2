/** @file demon.cc
 * @brief Funcions del Demon
 */
#include "ascended.hh"
#include "utils.hh"
using namespace pro2;

const int _ = -1;
const int h = black;  // dark red
const int b = 0x0000ff;
const int y = 0xffff00; // yellow
const int w = 0xffffff; // white
const int g = 0xdddd00; // gold

const std::vector<std::vector<int>> Ascended::ascended_sprite_ = {
    {_, _, y, y, y, y, y, y, y, y, y, y, y, y, y, y, _, _},
    {_, y, _, _, _, _, _, _, _, _, _, _, _, _, _, _, y, _},
    {_, y, _, _, _, _, _, _, _, _, _, _, _, _, _, _, y, _},
    {y, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, y},
    {y, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, y},
    {y, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, y},
    {y, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, y},
    {y, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, y},
    {y, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, y},
    {y, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, y},
    {y, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, y},
    {y, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, y},
    {y, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, y},
    {y, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, y},
    {y, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, y},
    {y, y, _, _, _, _, _, _, _, _, _, _, _, _, _, _, y, y},
    {_, y, _, _, _, _, _, _, _, _, _, _, _, _, _, _, y, _},
    {_, y, _, _, _, _, _, _, _, _, _, _, _, _, _, _, y, _},
    {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
};


void Ascended::activate(pro2::Pt mario_pos) {
    if (can_activate() && !active) {
        blessings.pop();  
        active = true;
        duration = 300;  
        pos_ = mario_pos;
    }
}

void Ascended::update(Pt mario_pos) {
    if (active) {
        pos_ = {mario_pos.x, mario_pos.y - 8}; 
        duration--;
        if (duration <= 0) {
            active = false;
        }
    }
}

// Get the shield's rectangle for collision detection
pro2::Rect Ascended::get_rect() const {
    int width = ascended_sprite_[0].size();
    int height = ascended_sprite_.size();
    return Rect{
        pos_.x - 9,
        pos_.y - 9,
        pos_.x + width - 9,
        pos_.y + height - 9
    };
}

// Paint the shield
void Ascended::paint(Window& window) const {
    if (active) {
        paint_sprite(window, {pos_.x - static_cast<int>(ascended_sprite_[0].size()/2), 
                                pos_.y - static_cast<int>(ascended_sprite_.size()/2)}, 
                    ascended_sprite_, false);
    }
}
