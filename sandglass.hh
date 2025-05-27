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

    bool is_in_cooldown_ = false;
    int cooldown_ = 15; //En segons
    int frame_counter_ = 0;  
    bool is_bright_ = false; 
    int animation_speed_ = 20;

	void apply_physics_();

    static const std::vector<std::vector<int>> sandglass_sprite_normal_;
	
    static const std::vector<std::vector<int>> sandglass_sprite_brighter_;
    
 public:
    Sandglass(pro2::Pt pos) : pos_(pos) {}

    Sandglass(pro2::Pt pos,pro2::Pt speed, int dist) : pos_(pos), ini_pos_(pos), speed_(speed),dist_(dist) {}

    void paint(pro2::Window& window) const;
    
     /**
     * @brief Retorna el valor privat touched_ 
     * 
     * @param window finestra on ho dibuixem
     * @param quantity nombre de Sandglasses a dibuixar
     * @param cx posició horitzontal
     * @param cy posició vertical
     */
    void paint(pro2::Window& window, int quantity, int cx, int cy) const;

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
     * @brief Actualitza el cooldown del efecte del item 
     * 
     * @param cooldown quanta estona durara l'item
     */
    void set_cooldown(int cooldown) { cooldown_ = cooldown; is_in_cooldown_ = true;}

    /**
     * @brief Retorna si esta o no en cooldown
     * 
     * @return Retorna un bool que et diu si esta en cooldown o no
     */
    int is_in_cooldown() { return is_in_cooldown_; }

    /**
     * @brief Retorna quant de temps li queda per acabar
     * 
     * @return Retorna cooldown_
     */
    int get_cooldown() { return cooldown_; }
};

#endif