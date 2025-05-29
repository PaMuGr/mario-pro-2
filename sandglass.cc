/** @file sandglass.cc
 * @brief Funcions del SandGlass
 */

#include "sandglass.hh"
#include "utils.hh"
using namespace std;
using namespace pro2;

const int _ = -1;
const int g = 0xa7c7cb;  // darkergreen
const int l = 0xdbe1e3; //glass l¡ght
const int s = 0xC2B280;  // dark red (blood)
const int br = 0x895129;  // brown wood

//Colors més brillants
const int g_bright  = 0xc7e7eb;  // brighter teal
const int l_bright  = 0xfbf1f3;  // near-white glass
const int s_bright  = 0xe2c890;  // warmer sand
const int br_bright = 0xa16131;  // lightened brown

// clang-format off
const vector<vector<int>> Sandglass::sandglass_sprite_normal_ = {
    {br, br, br, br, br, br, br, br, br, br, br},
        {_, g, g, l, l, l, l, l, g, g, _},
        {g, g, l, l, l, l, l, l, l, g, g},
        {g, l, l, l, l, l, l, l, l, l, g},
        {_, g, s, s, s, l, l, s, s, g, _},
        {_, _, g, s, s, s, s, s, g, _, _},
        {_, _, _, g, s, s, s, g, _, _, _},
        {_, _, _, _, g, s, g, _, _, _, _},
        {_, _, _, _, _, g, _, _, _, _, _},
        {_, _, _, _, g, s, g, _, _, _, _},
        {_, _, _, g, l, s, l, g, _, _, _},
        {_, _, g, l, l, s, l, l, g, _, _},
        {_, g, l, l, l, s, l, l, l, g, _},
        {g, l, l, l, s, s, l, l, l, l, g},
        {g, g, s, s, s, s, s, l, l, g, g},
        {_, g, g, s, s, s, s, s, g, g, _},
    {br, br, br, br, br, br, br, br, br, br, br}
};

const vector<vector<int>> Sandglass::sandglass_sprite_brighter_ = {
    {br_bright, br_bright, br_bright, br_bright, br_bright, br_bright, br_bright, br_bright, br_bright, br_bright, br_bright},
        {_, g_bright, g_bright, l_bright, l_bright, l_bright, l_bright, l_bright, g_bright, g_bright, _},
        {g, g_bright, l_bright, l_bright, l_bright, l_bright, l_bright, l_bright, l_bright, g_bright, g_bright},
        {g, l_bright, l_bright, l_bright, l_bright, l_bright, l_bright, l_bright, l_bright, l_bright, g_bright},
        {_, g_bright, s_bright, s_bright, s_bright, l_bright, l_bright, s_bright, s_bright, g_bright, _},
        {_, _, g_bright, s_bright, s_bright, s_bright, s_bright, s_bright, g_bright, _, _},
        {_, _, _, g_bright, s_bright, s_bright, s_bright, g_bright, _, _, _},
        {_, _, _, _, g_bright, s_bright, g_bright, _, _, _, _},
        {_, _, _, _, _, g_bright, _, _, _, _, _},
        {_, _, _, _, g_bright, s_bright, g_bright, _, _, _, _},
        {_, _, _, g_bright, l_bright, s_bright, l_bright, g_bright, _, _, _},
        {_, _, g_bright, l_bright, l_bright, s_bright, l_bright, l_bright, g_bright, _, _},
        {_, g_bright, l_bright, l_bright, l_bright, s_bright, l_bright, l_bright, l_bright, g_bright, _},
        {g, l_bright, l_bright, l_bright, s_bright, s_bright, l_bright, l_bright, l_bright, l_bright, g_bright},
        {g, g_bright, s_bright, s_bright, s_bright, s_bright, s_bright, l_bright, l_bright, g_bright, g_bright},
        {_, g_bright, g_bright, s_bright, s_bright, s_bright, s_bright, s_bright, g_bright, g_bright, _},
    {br_bright, br_bright, br_bright, br_bright, br_bright, br_bright, br_bright, br_bright, br_bright, br_bright, br_bright}
};
// clang-format on

void Sandglass::paint(pro2::Window& window) const {
    const Pt top_left = {pos_.x, pos_.y};
    if(is_bright_){
        paint_sprite(window, top_left, sandglass_sprite_brighter_, false);
    } else paint_sprite(window, top_left, sandglass_sprite_normal_, false);
}

pro2::Rect Sandglass::get_rect() const {
    const int width = 11;  
    const int height = 17;

    const int hitbox_width = 9;   
    const int hitbox_height = 15;

    return pro2::Rect({
        pos_.x + (width - hitbox_width) / 2,      // left
        pos_.y + (height - hitbox_height) / 2,    // top
        pos_.x + (width + hitbox_width) / 2,      // right
        pos_.y + (height + hitbox_height) / 2     // bottom
    });
}

void Sandglass::update(pro2::Window& window) {
    frame_counter_++;
    
    if (frame_counter_ % animation_speed_ == 0) {
        is_bright_ = !is_bright_;
    }

    if (is_active_) {
        effect_duration_--;
        if (effect_duration_ <= 0) {
            is_active_ = false;
            is_in_cooldown_ = true;
            respawn_delay_ = 240;  //5 segons abans de respawnejar
        }
        return;  
    }
    
    //Quan cooldown = 0 ->> pos random
    if (is_in_cooldown_) {
        respawn_delay_--;
        if (respawn_delay_ <= 0) {
            is_in_cooldown_ = false;
            
            pro2::Rect camera = window.camera_rect();
            //Agafem els punts del rectangle de camera
            int cam_left = camera.left;
            int cam_right = camera.right;
            int cam_top = camera.top;
            int cam_bottom = camera.bottom;
            
            //Calculem un marge de 20% aixi el objecte estarà a 10% de dalt i baix i dels costats 
            int width_margin = (cam_right - cam_left) * 0.1;
            int height_margin = (cam_bottom - cam_top) * 0.1;

            //Randomitzem els valors
            int new_x = randomizer(cam_right - width_margin, cam_left + width_margin);

            //Ens assegurem que no estigui massa abaix
            int min_y = cam_top + height_margin*2 + 50;
            int max_y = cam_top + (cam_bottom - cam_top) * 3 / 5;
            int new_y = randomizer(max_y, min_y);
            
            //Actualitzem posicions
            pos_.x = new_x;
            pos_.y = new_y;
        }
    }
}