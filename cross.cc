#include "cross.hh"
#include "utils.hh"
using namespace std;
using namespace pro2;

const int _ = -1;
const int h = pro2::black;
const int br = 0x895129;  // brown wood
const int db = 0x5c3a1e;  // dark brown wood
const int dr = 0x7c0a02;  // dark red (blood)

// clang-format off
const vector<vector<int>> Cross::cross_sprite_normal_ = {
    {_, _, _, _, db, db, db, db, _, _, _, _},
    {_, _, _, _, db, db, db, db, _, _, _, _},
    {_, _, _, _, db, db, db, db, _, _, _, _},
    {_, _, _, _, db, db, db, db, _, _, _, _},
    {_, _, _, _, db, br, db, db, _, _, _, _},
    {br, br, br, br, br, br, br, db, db, db, db, db}, 
    {br, h, br, br, br, br, br, br, br, db, h, db},  
    {db, db, db, db, br, br, br, br, db, db, db, db},
    {_, _, _, _, db, br, br, br, _, _, _, _},
    {_, _, _, _, db, db, br, br, _, _, _, _},
    {_, _, _, _, db, db, db, br, _, _, _, _},
    {_, _, _, _, db, db, db, db, _, _, _, _},
    {_, _, _, _, db, db, db, db, _, _, _, _},
    {_, _, _, _, db, db, db, db, _, _, _, _},
    {_, _, _, _, db, db, db, db, _, _, _, _},
    {_, _, _, _, dr, dr, dr, dr, _, _, _, _},
    {_, _, _, _, dr, dr, dr, dr, _, _, _, _},
};
// clang-format on

void Cross::paint(pro2::Window& window) const {
    paint(window, 1, pos_.x, pos_.y);
}

void Cross::paint(pro2::Window& window, int quantity, int cx, int cy) const {
    for(int i = 0; i < quantity; i++){
        Pt top_left = {static_cast<int>(cx + i * (cross_sprite_normal_[0].size() + 2)), cy};
        paint_sprite(window, top_left, cross_sprite_normal_, looking_left_);
    }
}

void Cross::apply_physics_() {
    if (grounded_) {
        speed_.y = 0;
    }
}

pro2::Rect Cross::hitbox(int height_y) const {
    int width = cross_sprite_normal_[0].size();
    int height = cross_sprite_normal_.size();
    return pro2::Rect({
        pos_.x,
        pos_.y + height_y,
        pos_.x + width,
        pos_.y + height_y + height
    });
}

void Cross::update(pro2::Window& window) {
    int distx = (pos_.x - ini_pos_.x);
    int disty = (pos_.y - ini_pos_.y);
    if (distx * distx + disty * disty > dist_ * dist_) {
        speed_.x = -speed_.x;
        speed_.y = -speed_.y;
    }
    pos_.x += speed_.x;
    pos_.y += speed_.y;
    
}