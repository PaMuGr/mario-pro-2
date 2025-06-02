/** @file mario.cc
 * @brief Funcions del Mario
 */

#include "mario.hh"
#include "utils.hh"
using namespace std;
using namespace pro2;

const int _ = -1;
const int r = pro2::red;
const int s = 0xecc49b;
//brown
const int br = 0x895129;
//dark brown
const int db = 0x5c3a1e;
//gold
const int gl = 0xFFD700;
//white
const int wh = 0xf2f3f4;

// clang-format off
const vector<vector<int>> Mario::mario_sprite_normal_ = {
    {_, _, _, br, br, br, br, br, _, _, _, _},
    {_, _, br, br, br, br, br, br, br, _, _, _},
    {_, _, br, br, br, s, s, br, s, _, _, _},
    {_, br, s, br, br, s, s, br, s, s, s, _},
    {_, br, s, br, br, br, s, s, br, s, s, s},
    {br, br, br, br, br, br, br, br, br, br, br, _},
    {br, br, br, br, br, br, br, br, br, br, _, _},
    {br, br, wh, wh, r, r, wh, wh, wh, wh, _, _},
    {_, wh, wh, wh, r, r, wh, wh, wh, wh, wh, _},
    {wh, wh, wh, wh, r, r, wh, wh, wh, wh, wh, wh},
    {s, s, wh, wh, r, r, r, wh, wh, wh, s, s},
    {s, s, s, wh, wh, r, r, r, r, s, s, s},
    {s, s, s, wh, wh, wh, r, r, r, s, s, s},
    {_, _, wh, wh, wh, _, _, wh, wh, wh, _, _},
    {_, s, br, s, _, _, _, _, s, br, s, _},
    {br, br, br, br, _, _, _, _, br, br, br, br},
};
// clang-format on

void Mario::paint(pro2::Window& window) const {
    const Pt top_left = {pos_.x - 6, pos_.y - 15};
    paint_sprite(window, top_left, mario_sprite_normal_, looking_left_);
}

void Mario::apply_physics_() {
    if (grounded_) {
        speed_.y = 0;
        accel_.y = 0;
    }

    // Always falling to check if we aren't grounded
    // If we are, we will return to the same spot

    const int gravity = 1;  // gravity = 1 pixel / frame_time^2
    speed_.y += gravity;

    if (accel_time_ > 0) {
        speed_.y += accel_.y;
        accel_time_--;
    }

    pos_.x += speed_.x;
    pos_.y += speed_.y;
}

void Mario::jump() {
    if (grounded_) {
        accel_.y = -6;
        grounded_ = false;
        accel_time_ = 2;
    }
}

pro2::Rect Mario::get_rect() const {
    return pro2::Rect({
        pos_.x - 6,           
        pos_.y - 15,         
        pos_.x + 6,           
        pos_.y + 1    
    });
}

void Mario::update(pro2::Window& window, const vector<Platform>& platforms) {
    last_pos_ = pos_;
    if (window.is_key_down(jump_key_)) {
        jump();
    }

    // Velocitat horitzontal
    speed_.x = 0; 
    if (window.is_key_down(left_key_)) {
        speed_.x = -SPEED;
    } else if (window.is_key_down(right_key_)) {
        speed_.x = SPEED;
    } 
    
    if (speed_.x != 0) {
        looking_left_ = speed_.x < 0;
    }

    apply_physics_();

    set_grounded(false);

    if (!window.is_key_down(go_down_key_)) {
        for (const Platform& platform : platforms) {
            if (platform.has_crossed_floor_downwards(last_pos_, pos_)) {
                set_grounded(true);
                set_y(platform.top());
            }
        }
    }
}