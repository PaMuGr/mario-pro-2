/** @file mario.hh
 * @brief Especificacions de Funcions del Mario
 */

#ifndef MARIO_HH
#define MARIO_HH

#include <iostream>
#include <vector>
#include "platform.hh"
#include "window.hh"

class Mario {
 private:
    pro2::Pt pos_, last_pos_;
    pro2::Pt speed_ = {0, 0};
    pro2::Pt accel_ = {0, 0};
    int      accel_time_ = 0;
    int redemtionPoints_ = 0;
    int mario_width = 6;
    int mario_height = 8;
    int jump_key_, left_key_, right_key_;

    bool grounded_ = false;
	bool looking_left_ = false;

	void apply_physics_();
	
 public:
    Mario(pro2::Pt pos, int jumpKey, int leftKey, int rightKey) : pos_(pos), 
    last_pos_(pos), 
    jump_key_(jumpKey),
    left_key_(leftKey),
    right_key_(rightKey)
    {}

     /**
     * @brief Augmenta en 1 la puntuació
     */
    void add_points(){
        redemtionPoints_++;
    }

     /**
     * @brief Retorna el valor privat touched_ 
     * 
     * @return int amb els punts que té al moment
     */
    int check_points() const{
        return redemtionPoints_;
    }

    void paint(pro2::Window& window) const;

    pro2::Pt pos() const {
        return pos_;
    }

    void set_y(int y) {
        pos_.y = y;
    }

    bool is_grounded() const {
        return grounded_;
    }

    void set_grounded(bool grounded) {
        grounded_ = grounded;
        if (grounded_) {
            speed_.y = 0;
        }
    }

    void toggle_grounded() {
        set_grounded(!grounded_);
    }

    void jump();

    /**
     * @brief Retorna la hitbox del mario 
     */
    pro2::Rect get_rect() const;

    void update(pro2::Window& window, const std::vector<Platform>& platforms);

 private:
    static const std::vector<std::vector<int>> mario_sprite_normal_;
};

#endif