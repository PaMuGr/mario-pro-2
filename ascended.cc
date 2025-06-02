/** @file demon.cc
 * @brief Funcions del Demon
 */
#include "ascended.hh"
#include "utils.hh"
using namespace pro2;

const int _ = -1;
const int h = black;  // dark red
const int b = 0x63697A;

const vector<vector<int>> Ascended::ascended_sprite_ = {
    {_, _, _, _, _, b, b, b, b, b, b, _, _, _, _, _},
    {_, _, _, _, b, b, b, b, b, b, b, b, _, _, _, _},
    {_, _, _, b, b, _, _, _, _, _, _, b, b, _, _, _},
    {_, _, b, b, _, _, _, _, _, _, _, _, b, b, _, _},
    {_, b, b, _, _, _, _, _, _, _, _, _, _, b, b, _},
    {b, b, _, _, _, _, _, _, _, _, _, _, _, _, b, b},
    {b, _, _, _, _, _, _, _, _, _, _, _, _, _, _, b},
    {b, _, _, _, _, _, _, _, _, _, _, _, _, _, _, b},
    {b, _, _, _, _, _, _, _, _, _, _, _, _, _, _, b},
    {b, _, _, _, _, _, _, _, _, _, _, _, _, _, _, b},
    {b, _, _, _, _, _, _, _, _, _, _, _, _, _, _, b},
    {b, _, _, _, _, _, _, _, _, _, _, _, _, _, _, b},
    {b, _, _, _, _, _, _, _, _, _, _, _, _, _, _, b},
    {b, b, _, _, _, _, _, _, _, _, _, _, _, _, b, b},
    {_, b, b, _, _, _, _, _, _, _, _, _, _, b, b, _},
    {_, _, b, b, _, _, _, _, _, _, _, _, b, b, _, _},
    {_, _, _, b, b, _, _, _, _, _, _, b, b, _, _, _},
    {_, _, _, _, b, b, b, b, b, b, b, b, _, _, _, _},
    {_, _, _, _, _, b, b, b, b, b, b, _, _, _, _, _}
};
// clang-format on

Ascended::Ascended(const Pt& pos, int duration) 
    : pos_(pos), active_(false), duration_(duration) {}

void Ascended::activate(const Pt& pos, int duration) {
    pos_ = pos;
    active_ = true;
    duration_ = duration;
}

void Ascended::update() {
    if (active_) {
        duration_--;
        if (duration_ <= 0) {
            active_ = false;
        }
    }
}

void Ascended::paint(Window& window) const {
    if (active_) {
        paint_sprite(window, pos_, ascended_sprite_, false);
    }
}

pro2::Rect Ascended::get_rect() const {
    if (!active_) return {0, 0, 0, 0};
    
    int width = ascended_sprite_[0].size();
    int height = ascended_sprite_.size();
    return Rect{
        pos_.x,
        pos_.y,
        pos_.x + width,
        pos_.y + height
    };
}
