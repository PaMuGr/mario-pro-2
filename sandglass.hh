/** @file sandglass.hh
 * @brief Especificació de les Funcions del SandGlass
 */

#ifndef SANDGLASS_HH
#define SANDGLASS_HH

#include <iostream>
#include <vector>
#include <list>
#include "platform.hh"
#include "window.hh"
#include "geometry.hh"

class Sandglass {
 private:
    pro2::Pt pos_,ini_pos_;
    pro2::Pt speed_ = {0, 0};
    int dist_ = 0;

    int frame_counter_ = 0;  
    bool is_bright_ = false; 
    int animation_speed_ = 20;

    bool is_active_ = false;         //Efecte actiu
    bool is_in_cooldown_ = false;    //Esperant per respawnejar
    int effect_duration_ = 0;        //Duració de l'efecte 
    int respawn_delay_ = 0;          //Temps abans d'apareixer de nou
    
	void apply_physics_();

    static const std::vector<std::vector<int>> sandglass_sprite_normal_;
    static const std::vector<std::vector<int>> sandglass_sprite_brighter_;
    
 public:
    Sandglass(pro2::Pt pos) : pos_(pos) {}
    Sandglass(pro2::Pt pos,pro2::Pt speed, int dist) : pos_(pos), ini_pos_(pos), speed_(speed),dist_(dist) {}

    void paint(pro2::Window& window) const;
    
    /**
     * @brief Retorna la posicio a la que es troba la Sandglass 
     * 
     * @returns Un Pt amb la posició x i y de la Sandglass
     */
    pro2::Pt pos() const {
        return pos_;
    }

    /**
     * @brief Canvia la posició horitzontal per x 
     * 
     * @param x Posició a intercanviar
     */
    void set_x(int x) {
        pos_.x = x;
    }

    /**
     * @brief Canvia la posició vertical per y
     * 
     * @param y Posició a intercanviar
     */
    void set_y(int y) {
        pos_.y = y;
    }

     /**
     * @brief Crea una hitbox utilitzant height_y
     * 
     * @param height_y altura que te al moment la Sandglass
     * 
     * @returns Un Rectangle amb la hitbox de Sandglass
     */
    pro2::Rect get_rect() const;

    /**
     * @brief Actualitza el moviment de la creu 
     * 
     * @param window finestra on ho dibuixem
     */
    void update(pro2::Window& window);

    /**
     * @brief Actualitza quin sprite utilitzem a un més brillant
     * 
     * @param bright si == true bright
     */
    void set_bright(bool bright) { is_bright_ = bright; }

    /**
     * @brief Activa l'efecte del Sandglass (inicia el temps actiu)
     */
    void activate(int total_duration, int effect_frames) {
        is_active_ = true;
        is_in_cooldown_ = true;
        effect_duration_ = effect_frames;
        respawn_delay_ = total_duration - effect_frames;
    }

    /**
     * @brief Retorna si està en fase de cooldown (esperant reapareixer)
     */
    bool is_in_cooldown() const { return is_in_cooldown_; }

    /**
     * @brief Retorna si l'efecte està actiu
     */
    bool is_effect_active() const { return is_active_; }
};

#endif