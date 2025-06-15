/** 
 * @file mario.hh
 * @brief Definició de la classe Mario per al control del personatge principal del joc.
 */

#ifndef MARIO_HH
#define MARIO_HH

#include "list.hh"
#include "platform.hh"
#include "window.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <vector>
#endif

/**
 * @class Mario
 * @brief Representa el personatge principal amb moviment, física i estadístiques.
 * 
 * Aquesta classe gestiona la posició, la física (acceleració, velocitat),
 * les puntuacions, el control per teclat i el dibuix del personatge.
 */
class Mario {
 private:
    pro2::Pt pos_;          ///< Posició actual de Mario
    pro2::Pt last_pos_;     ///< Posició anterior de Mario
    pro2::Pt speed_ = {0, 0}; ///< Velocitat actual
    pro2::Pt accel_ = {0, 0}; ///< Acceleració actual
    int accel_time_ = 0;    ///< Comptador per acceleració temporal
    int redemtionPoints_ = 0; ///< Punts acumulats pel jugador
    int sandwatchCollected_ = 0; ///< Nombre de sandwatches recollits
    int mario_width = 6;    ///< Amplada del sprite de Mario
    int mario_height = 8;   ///< Alçada del sprite de Mario

    int jump_key_;          ///< Codi tecla per saltar
    int left_key_;          ///< Codi tecla per anar a l'esquerra
    int right_key_;         ///< Codi tecla per anar a la dreta
    int go_down_key_;       ///< Codi tecla per anar cap avall

    int SPEED = 6;          ///< Velocitat base

    bool grounded_ = false; ///< Indica si Mario està en terra
	bool looking_left_ = false; ///< Indica si Mario mira cap a l'esquerra

    /**
     * @brief Aplica la física (velocitat i acceleració) a Mario.
     */
	void apply_physics_();
	
 public:
    /**
     * @brief Constructor de Mario.
     * @param pos Posició inicial
     * @param jumpKey Codi de tecla per saltar
     * @param leftKey Codi de tecla per anar a l'esquerra
     * @param rightKey Codi de tecla per anar a la dreta
     * @param godownKey Codi de tecla per anar cap avall
     */
    Mario(pro2::Pt pos, int jumpKey, int leftKey, int rightKey, int godownKey) : pos_(pos), 
    last_pos_(pos), 
    jump_key_(jumpKey),
    left_key_(leftKey),
    right_key_(rightKey),
    go_down_key_(godownKey)
    {}

    /**
     * @brief Augmenta en 1 la puntuació
     */
    void add_points(){
        redemtionPoints_++;
    }

    /**
     * @brief Augmenta en 1 els sandwatched collected
     */
    void collect_sandwatch(){
        sandwatchCollected_++;
    }

    /**
     * @brief Retorna el valor privat sandwatchCollected 
     * 
     * @return int amb els sandwatches que ha recollit
     */
    int sandwatches_collected() const{
        return sandwatchCollected_;
    }

     /**
     * @brief Retorna el valor privat redemtionPoints_ 
     * 
     * @return int amb els punts que té al moment
     */
    int check_points() const{
        return redemtionPoints_;
    }

    /**
     * @brief Dibuixa el sprite de Mario a la finestra.
     * @param window Finestra on es dibuixa Mario
     */
    void paint(pro2::Window& window) const;

    /**
     * @brief Retorna la posició actual de Mario.
     * @return Posició actual
     */
    pro2::Pt pos() const {
        return pos_;
    }

    /**
     * @brief Estableix la coordenada y de Mario.
     * @param y Nova coordenada y
     */
    void set_y(int y) {
        pos_.y = y;
    }

    /**
     * @brief Estableix la coordenada x de Mario.
     * @param x Nova coordenada x
     */
    void set_x(int x) {
        pos_.x = x;
    }

    /**
     * @brief Indica si Mario està en terra.
     * @return true si està en terra, false altrament
     */
    bool is_grounded() const {
        return grounded_;
    }

    /**
     * @brief Canvia l'estat d'estar en terra o no.
     * @param grounded Nou estat de terra
     */
    void set_grounded(bool grounded) {
        grounded_ = grounded;
        if (grounded_) {
            speed_.y = 0;
        }
    }

     /**
     * @brief Canvia l'estat de terra al contrari del que tenia.
     */
    void toggle_grounded() {
        set_grounded(!grounded_);
    }

    /**
     * @brief Fa que Mario salti si està en terra.
     */
    void jump();

    /**
     * @brief Retorna la hitbox del mario 
     */
    pro2::Rect get_rect() const;

    void update(pro2::Window& window, const std::vector<Platform>& platforms);

 private:
    static const std::vector<std::vector<int>> mario_sprite_normal_; ///< Sprite de Mario normal
};

#endif