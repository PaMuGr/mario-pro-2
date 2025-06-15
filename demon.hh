/** @file demon.hh
* @brief Especificació de la Classe Demon
*/

#ifndef DEMON_HH
#define DEMON_HH

#include "window.hh"
#include "geometry.hh"
#include "platform.hh"
#include "list.hh"

#ifndef NO_DIAGRAM
#include <set>
#include <vector>
#endif


class Fireball{
 private:
    pro2::Pt pos_;
    pro2::Pt speed_;
    bool falling_;
    int duracio_; 
    int duracio_fire = 2*48;

    static const std::vector<std::vector<int>> fireball_sprite_;
    static const std::vector<std::vector<int>> fire_sprite_;

 public: 
   
    Fireball() : pos_({0,0}), speed_({0,0}), falling_(true) {}
    
    Fireball(pro2::Pt pos, pro2::Pt speed);

    void update(pro2::Window& window,const std::set<const Platform*>& platforms);
    void paint(pro2::Window& window) const;

    pro2::Pt pos() const {
        return pos_;
    }

    /**
     * @brief Retorna el rectangle del objecte
     * 
     * @return un Rectangle corresponent al objecte
     */
    pro2::Rect get_rect() const;

    void start_fire(){
        pos_.y -= 2;
        falling_ = false;
        duracio_ = duracio_fire;
    }

    /**
     * @brief Retorna si esta o no cayent el fireball
     * 
     * @return El bool falling_
     */
    bool is_falling() const { return falling_; }

    /**
     * @brief Retorna si esta encara actiu el foc
     * 
     * @return Comprovació de si el foc esta o no apagat
     */
    bool is_expired() const { return !falling_ && duracio_ <= 0; }
    
};






class Demon {

    friend class Fireball;
 private:
    pro2::Pt pos_;
    pro2::Pt speed_ = {0, 0};
    int fire_cooldown_; //Cooldown
    int fire_rate_; //Dispars per segons
    bool is_decayed_ = false;
    List<Fireball> fireballs_;
    

    //Velocitat del dimoni
      int demon_speed_ = 4; 

    static const std::vector<std::vector<int>> demon_sprite_;

    static const std::vector<std::vector<int>> decayed_demon_sprite_;
	
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
    void update(pro2::Window& window,const std::set<const   Platform*>& platforms);
    

    /**
     * @brief Retorna si ha acabat amb les bales i ha de tornar a disparar
     */
    bool should_shoot() const;
    
    /**
     * @brief Posa del nou el cooldown a fire rate
     */
    void reset_cooldown(){fire_cooldown_ = fire_rate_;}

    /**
     * @brief Canvi d'estat el dimoni
     */
    void decaying(){
        is_decayed_ = true;
        demon_speed_ = 5;
    }

    void try_shoot_fireball();
    void update_fireballs(pro2::Window& window,const std::set<const Platform*>& platforms);
    bool check_fireball_collisions(const pro2::Rect& marioRect, const pro2::Rect& ascendedRect);



};



#endif