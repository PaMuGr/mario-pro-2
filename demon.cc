/** @file demon.cc
 * @brief Funcions del Demon
 */
#include "demon.hh"
#include "utils.hh"
using namespace pro2;
using namespace std;

const int _ = -1;
const int h = black;  // dark red
const int o = 0xFF6600;  // orange
const int y = 0xFFFF00;  // yellow
const int d = 0x7c0a02;  // dark red
const int g = 0x808080;  // grey bonish
const int t = 0xA9A9A9;
const int r = 0x860111;

//decayed mode
const int B = 0x2b0000;     // dark red 
const int C = 0x5a0101;     // very dark red 
const int D = 0x606060;     // dark grey    
const int E = 0x888888;     // mid grey      
const int F = 0x4c0000;     // ultra dark red 

// clang-format off
const vector<vector<int>> Demon::demon_sprite_ = {
    {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, t, t, _, _, _, _, _, _, _, _, _, t, t, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _}, 
    {_, _, _, _, _, _, _, _, _, g, _, _, _, _, _, _, _, _, _, t, t, _, _, _, _, _, _, _, t, t, _, _, _, _, _, _, _, _, _, g, _, _, _, _, _, _, _, _, _}, 
    {_, _, _, _, _, _, _, _, g, g, g, _, _, _, _, _, _, _, _, _, t, t, _, _, _, _, _, t, t, _, _, _, _, _, _, _, _, _, g, g, g, _, _, _, _, _, _, _, _}, 
    {g, g, g, g, g, g, g, g, g, g, g, g, _, _, _, _, _, _, _, _, _, t, t, _, _, _, t, t, _, _, _, _, _, _, _, _, _, g, g, g, g, g, g, g, g, g, g, g, g}, 
    {h, g, g, g, g, g, g, g, g, g, g, g, g, g, _, _, _, _, _, _, r, t, t, r, _, r, t, t, r, _, _, _, _, _, _, _, g, g, g, g, g, g, g, g, g, g, g, g, h}, 
    {_, h, h, d, d, d, d, d, g, g, g, d, g, g, g, g, g, g, g, r, r, t, r, r, r, r, r, t, r, r, g, g, g, g, g, g, g, g, g, g, g, d, d, d, d, d, h, h, _}, 
    {_, _, h, d, d, d, d, g, g, g, d, d, d, g, g, g, g, g, g, r, r, h, h, h, r, h, h, h, r, r, g, g, g, g, g, g, g, d, d, g, g, g, d, d, d, d, h, _, _}, 
    {_, _, _, h, d, d, g, g, g, d, d, d, d, d, d, g, g, d, d, r, r, r, h, h, r, h, h, r, r, r, d, d, g, g, d, d, d, d, d, d, g, g, g, d, d, h, _, _, _}, 
    {_, _, _, _, h, g, g, g, d, d, d, d, d, d, g, g, d, d, d, r, r, r, r, h, r, h, r, r, r, r, d, d, d, g, g, d, d, d, d, d, d, g, g, g, h, _, _, _, _}, 
    {_, _, _, _, g, g, h, d, d, d, d, d, d, g, g, d, d, d, d, r, r, r, r, r, r, r, r, r, r, r, d, d, d, d, g, g, d, d, d, d, d, d, h, g, g, _, _, _, _}, 
    {_, _, _, _, g, g, _, h, d, d, d, d, g, g, d, d, d, d, d, r, r, r, r, h, r, h, r, r, r, r, d, d, d, d, d, g, g, d, d, d, d, h, _, g, g, _, _, _, _}, 
    {_, _, _, _, g, _, _, _, h, d, d, g, g, d, d, d, d, d, h, r, h, h, r, r, r, r, r, h, h, r, h, d, d, d, d, d, g, g, d, d, h, _, _, _, g, _, _, _, _}, 
    {_, _, _, _, _, _, _, _, _, h, g, g, d, d, d, d, h, h, _, r, r, h, h, h, r, h, h, h, r, r, _, h, h, d, d, d, d, g, g, h, _, _, _, _, _, _, _, _, _}, 
    {_, _, _, _, _, _, _, _, _, g, g, h, h, h, h, h, _, _, _, _, r, r, h, h, h, h, h, r, r, _, _, _, _, h, h, h, h, h, g, g, _, _, _, _, _, _, _, _, _}, 
    {_, _, _, _, _, _, _, _, _, g, _, _, _, _, _, _, _, _, _, _, _, r, r, r, h, r, r, r, _, _, _, _, _, _, _, _, _, _, _, g, _, _, _, _, _, _, _, _, _}, 
    {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, r, r, r, r, r, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _}, 
};

const vector<vector<int>> Demon::decayed_demon_sprite_ = {
    {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, E, E, _, _, _, _, _, _, _, _, _, E, E, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _}, 
    {_, _, _, _, _, _, _, _, _, D, _, _, _, _, _, _, _, _, _, E, E, _, _, _, _, _, _, _, E, E, _, _, _, _, _, _, _, _, _, D, _, _, _, _, _, _, _, _}, 
    {_, _, _, _, _, _, _, _, D, D, D, _, _, _, _, _, _, _, _, _, E, E, _, _, _, _, _, E, E, _, _, _, _, _, _, _, _, _, D, D, D, _, _, _, _, _, _, _, _}, 
    {D, D, D, D, D, D, D, D, D, D, D, D, _, _, _, _, _, _, _, _, _, E, E, _, _, _, E, E, _, _, _, _, _, _, _, _, _, D, D, D, D, D, D, D, D, D, D, D, D}, 
    {B, D, D, D, D, D, D, D, D, D, D, D, D, D, _, _, _, _, _, _, F, E, E, F, _, F, E, E, F, _, _, _, _, _, _, _, D, D, D, D, D, D, D, D, D, D, D, D, B}, 
    {_, B, B, C, C, C, C, C, D, D, D, C, D, D, D, D, D, D, D, F, F, E, F, F, F, F, F, E, F, F, D, D, D, D, D, D, D, D, D, D, D, C, C, C, C, C, B, B, _}, 
    {_, _, B, C, C, C, C, D, D, D, C, C, C, D, D, D, D, D, D, F, F, B, B, B, F, B, B, B, F, F, D, D, D, D, D, D, D, C, C, D, D, D, C, C, C, C, B, _, _}, 
    {_, _, _, B, C, C, D, D, D, C, C, C, C, C, C, D, D, C, C, F, F, F, B, B, F, B, B, F, F, F, C, C, D, D, C, C, C, C, C, C, D, D, D, C, C, B, _, _, _}, 
    {_, _, _, _, B, D, D, D, C, C, C, C, C, C, D, D, C, C, C, F, F, F, F, B, F, B, F, F, F, F, C, C, C, D, D, C, C, C, C, C, C, D, D, D, B, _, _, _, _}, 
    {_, _, _, _, D, D, B, C, C, C, C, C, C, D, D, C, C, C, C, F, F, F, F, F, F, F, F, F, F, F, C, C, C, C, D, D, C, C, C, C, C, C, B, D, D, _, _, _, _}, 
    {_, _, _, _, D, D, _, B, C, C, C, C, D, D, C, C, C, C, C, F, F, F, F, B, F, B, F, F, F, F, C, C, C, C, C, D, D, C, C, C, C, B, _, D, D, _, _, _, _}, 
    {_, _, _, _, D, _, _, _, B, C, C, D, D, C, C, C, C, C, B, F, B, B, F, F, F, F, F, B, B, F, B, C, C, C, C, C, D, D, C, C, B, _, _, _, D, _, _, _, _}, 
    {_, _, _, _, _, _, _, _, _, B, D, D, C, C, C, C, B, B, _, F, F, B, B, B, F, B, B, B, F, F, _, B, B, C, C, C, C, D, D, B, _, _, _, _, _, _, _, _, _}, 
    {_, _, _, _, _, _, _, _, _, D, D, B, B, B, B, B, _, _, _, _, F, F, B, B, B, B, B, F, F, _, _, _, _, B, B, B, B, B, D, D, _, _, _, _, _, _, _, _, _}, 
    {_, _, _, _, _, _, _, _, _, D, _, _, _, _, _, _, _, _, _, _, _, F, F, F, B, F, F, F, _, _, _, _, _, _, _, _, _, _, _, D, _, _, _, _, _, _, _, _, _}, 
    {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, F, F, F, F, F, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _}, 
};


const vector<vector<int>> Fireball::fireball_sprite_ = {
    {_, _, y, y, y, y, _, _},
    {_, y, o, o, o, o, y, _},
    {y, o, r, r, r, r, o, y},
    {y, o, r, d, d, r, o, y},
    {y, o, r, d, d, r, o, y},
    {y, o, r, r, r, r, o, y},
    {_, y, o, o, o, o, y, _},
    {_, _, y, y, y, y, _, _}
};
// clang-format on

const vector<vector<int>> Fire::fire_sprite_ = {
    {y, _, y, y, y, _, _, _},
    {y, y, y, o, o, y, _, _},
    {y, y, o, r, r, o, y, _},
    {_, y, o, r, d, o, y, _},
    {_, y, o, r, d, o, y, _},
    {_, _, y, d, r, o, y, _},
    {_, _, y, o, o, o, y, _},
    {_, _, _, y, y, y, _, _}
};

void Demon::update(pro2::Window& window) {
    //Marges de la camera
    pro2::Rect camera_rect = window.camera_rect();
    int camera_left = camera_rect.left + 50;
    int camera_right = camera_rect.right - 50;
    
    //Movem el dimoni
    pos_.x += speed_.x;

    //Canvi de direcció
    if (pos_.x <= camera_left) {
        pos_.x = camera_left;
        speed_.x = demon_speed_; 
    } 
    else if (pos_.x + demon_sprite_[0].size() >= camera_right) {
        pos_.x = camera_right - demon_sprite_[0].size();
        speed_.x = -demon_speed_; 
    }

    //Mantenint el dimoni a dalt
    pos_.y = camera_rect.top + 10;

    if (fire_cooldown_ > 0) {
        fire_cooldown_--;
    }
}

pro2::Rect Demon::get_rect() const {
    int width = demon_sprite_[0].size();
    int height = demon_sprite_.size();
    return pro2::Rect({
        pos_.x,
        pos_.y,
        pos_.x + width,
        pos_.y + height
    });
}

bool Demon::should_shoot() const {
    return fire_cooldown_ == 0;
}

void Demon::paint(pro2::Window& window) const {
    if(!is_decayed_){
        paint_sprite(window, pos_, demon_sprite_, false);
    } else  paint_sprite(window, pos_, decayed_demon_sprite_, false);
}

/*######### IMPLEMENTACIÓ FIREBALL #########*/

Fireball::Fireball(pro2::Pt pos, pro2::Pt speed) 
    : pos_(pos), speed_(speed), active_(true) {}

void Fireball::update(pro2::Window& window) {
    pos_.x += speed_.x;
    pos_.y += speed_.y;
    
    //Si fora de lloc desactivar
    if (pos_.y > window.camera_rect().bottom) {
        active_ = false;
    }
}

void Fireball::paint(pro2::Window& window) const {
    if (active_) {
        paint_sprite(window, pos_, fireball_sprite_, false);
    }
}

pro2::Rect Fireball::get_rect() const {
    int width = fireball_sprite_[0].size();
    int height = fireball_sprite_.size();
    return pro2::Rect({
        pos_.x,
        pos_.y,
        pos_.x + width,
        pos_.y + height
    });
}

/*############ IMPLEMENTACIÓ FOC ##############*/

void Fire::update() {
    if (active_) {
        duracio_--;
        if (duracio_ <= 0) {
            active_ = false;
        }
    }
}

void Fire::paint(pro2::Window& window) const {
    if (active_) {
        paint_sprite(window, pos_, fire_sprite_, false);
    }
}

pro2::Rect Fire::get_rect() const {
    int width = fire_sprite_[0].size();
    int height = fire_sprite_.size();
    return pro2::Rect({
        pos_.x,
        pos_.y,
        pos_.x + width,
        pos_.y + height
    });
}
