/** @file cross.hh
 *  @brief Especificació de la classe Cross.
 *
 *  Aquesta classe representa una creu col·leccionable amb moviment,
 *  física bàsica i representació gràfica dins el joc.
 */

#ifndef CROSS_HH
#define CROSS_HH

#include "platform.hh"
#include "window.hh"
#include "geometry.hh"
#include "list.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <vector>
#include <list>
#endif

/**
 * @class Cross
 * @brief Classe que representa una creu amb moviment i interacció física.
 *
 * Les creus poden moure’s, detectar si toquen terra (grounded), i ser dibuixades
 * tant de forma individual com agrupada. També poden generar una hitbox per a col·lisions.
 */
class Cross {
 private:
    pro2::Pt pos_,ini_pos_;
    pro2::Pt speed_ = {0, 0};
    int dist_ = 0;
    
    bool grounded_ = false;
	bool looking_left_ = false;

	void apply_physics_();

    static const std::vector<std::vector<int>> cross_sprite_normal_;
	
 public:
    Cross() : pos_({0,0}), ini_pos_({0,0}), speed_({0,0}), dist_(0), grounded_(false), looking_left_(false) {}

    Cross(pro2::Pt pos) : pos_(pos), ini_pos_(pos) {}

    Cross(pro2::Pt pos,pro2::Pt speed, int dist) : pos_(pos), ini_pos_(pos), speed_(speed), dist_(dist) {}

    void paint(pro2::Window& window) const;
    
     /**
     * @brief Retorna el valor privat touched_ 
     * 
     * @param window finestra on ho dibuixem
     * @param quantity nombre de crosses a dibuixar
     * @param cx posició horitzontal
     * @param cy posició vertical
     */
    void paint(pro2::Window& window, int quantity, int cx, int cy) const;

    /**
     * @brief Retorna la posicio a la que es troba la cross 
     * 
     * @returns Un Pt amb la posició x i y de la cross
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
     * @brief Canvia la posició vertical per y
     * 
     * @param y Posició a intercanviar
     * 
     * @returns Un Pt amb la posició x i y de la cross
     */
    bool is_grounded() const {
        return grounded_;
    }

     /**
     * @brief Crea una hitbox utilitzant height_y
     * 
     * @param height_y altura que te al moment la cross
     * 
     * @returns Un Rectangle amb la hitbox de cross
     */
    pro2::Rect get_rect(int height_y = 0) const;

    /**
     * @brief actualitza el moviment de la creu 
     * 
     * @param window finestra on ho dibuixem
     */
    void update(pro2::Window& window);
};

#endif