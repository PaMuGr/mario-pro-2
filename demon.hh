/** @file demon.hh
 * @brief Especificació de la Classe Demon
 */

#ifndef DEMON_HH
#define DEMON_HH

#include "window.hh"
#include "geometry.hh"
#include <vector>

class Demon {
 private:
    pro2::Pt pos_;
    pro2::Pt speed_ = {0, 0};
    int fire_cooldown_; //Cooldown
    int fire_rate_; //Dispars per segons

    //Velocitat del dimoni
      int DEMON_SPEED = 4; 

    static const std::vector<std::vector<int>> demon_sprite_;
	
 public:
    Demon() : pos_({0,0}), speed_({0,0}), fire_cooldown_(0), fire_rate_(12) {}

    Demon(pro2::Pt pos) 
        : pos_(pos), speed_({0, 0}), 
          fire_cooldown_(0), fire_rate_(12) {} //Dispars cada 0.25 segons

    void paint(pro2::Window& window) const;

    /**
     * @brief Retorna la posició 
     * 
     * @returns Un Pt amb la pos_ del demon
     */
    pro2::Pt pos() const { return pos_; }

     /**
     * @brief Crea una hitbox 
     * 
     * @returns Un Rectangle amb la hitbox de demon
     */
    pro2::Rect get_rect() const;

    /**
     * @brief actualitza el moviment del Demon 
     * 
     * @param window finestra on ho dibuixem
     */
    void update(pro2::Window& window);

    /**
     * @brief Retorna si ha acabat amb les bales i ha de tornar a disparar
     */
    bool should_shoot() const;
    
    /**
     * @brief Posa del nou el cooldown a fire rate
     */
    void reset_cooldown(){fire_cooldown_ = fire_rate_;}
};

class Fireball{
 private:
    pro2::Pt pos_;
    pro2::Pt speed_;
    bool active_;

    static const std::vector<std::vector<int>> fireball_sprite_;

 public: 
   
    Fireball() : pos_({0,0}), speed_({0,0}), active_(false) {}
    
    Fireball(pro2::Pt pos, pro2::Pt speed);

    void update();
    void paint(pro2::Window& window) const;

    /**
     * @brief Retorna si esta actiu o no la fireball
     */
    bool is_active() const{return active_;}
    pro2::Rect get_rect() const;
    void deactivate(){active_ = false;}
};

class Fire {
private:
    pro2::Pt pos_;
    int duracio_; 
    bool active_;

    static const std::vector<std::vector<int>> fire_sprite_;

public:
    Fire() : pos_({0,0}), duracio_(0), active_(false) {}
    
    Fire(pro2::Pt pos, int lifetime) : pos_(pos), duracio_(lifetime), active_(true) {}

    void update();

    void paint(pro2::Window& window) const;
    
    void deactivate_fires(){active_ = false;}

    pro2::Rect get_rect() const;

    bool is_active() const { return active_; }
};

#endif