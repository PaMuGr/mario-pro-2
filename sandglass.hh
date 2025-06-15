/** 
 * @file sandglass.hh
 * @brief Especificació de la classe Sandglass que representa un rellotge de sorra al joc.
 */

#ifndef SANDGLASS_HH
#define SANDGLASS_HH

#include "platform.hh"
#include "window.hh"
#include "geometry.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <vector>
#include <list>
#endif

/**
 * @class Sandglass
 * @brief Representa un rellotge de sorra que el jugador pot recollir i activar.
 * 
 * La classe gestiona la posició, moviment, animació i estat d'activació del rellotge.
 * També controla els períodes d'activació i cooldown (respawn).
 */
class Sandglass {
 private:
    pro2::Pt pos_;             ///< Posició actual del rellotge
    pro2::Pt ini_pos_;         ///< Posició inicial del rellotge
    pro2::Pt speed_ = {0, 0};  ///< Velocitat del rellotge (si es mou)
    int dist_ = 0;             ///< Distància recorreguda (o un altre propòsit, segons implementació)

    int frame_counter_ = 0;    ///< Comptador de frames per animació
    bool is_bright_ = false;   ///< Flag per a canviar a sprite més brillant
    int animation_speed_ = 20; ///< Velocitat de l'animació (frames)

    bool is_active_ = false;         ///< Indica si l'efecte està actiu
    bool is_in_cooldown_ = false;    ///< Indica si està en període de cooldown (esperant reapareixer)
    int effect_duration_ = 0;        ///< Durada restant de l'efecte actiu (frames)
    int respawn_delay_ = 0;          ///< Temps restant abans de reapareixer (frames)
    
    /// Aplica la física al rellotge (moviment, gravetat, etc.)
	void apply_physics_();

    static const std::vector<std::vector<int>> sandglass_sprite_normal_;   ///< Sprite normal
    static const std::vector<std::vector<int>> sandglass_sprite_brighter_; ///< Sprite brillant
    
 public:
    /**
     * @brief Constructor bàsic amb posició inicial
     * @param pos Posició inicial del rellotge
     */
    Sandglass(pro2::Pt pos) : pos_(pos) {}

    /**
     * @brief Constructor complet amb posició, velocitat i distància
     * @param pos Posició inicial
     * @param speed Velocitat inicial
     * @param dist Distància (ús específic)
     */
    Sandglass(pro2::Pt pos, pro2::Pt speed, int dist) 
        : pos_(pos), ini_pos_(pos), speed_(speed), dist_(dist) {}

    /**
     * @brief Dibuixa el rellotge a la finestra indicada.
     * @param window Finestra on pintar el rellotge
     */
    void paint(pro2::Window& window) const;
    
    /**
     * @brief Retorna la posició actual del rellotge.
     * @return Posició (Pt) del rellotge
     */
    pro2::Pt pos() const {
        return pos_;
    }

    /**
     * @brief Canvia la posició horitzontal del rellotge.
     * @param x Nova coordenada X
     */
    void set_x(int x) {
        pos_.x = x;
    }

    /**
     * @brief Canvia la posició vertical del rellotge.
     * @param y Nova coordenada Y
     */
    void set_y(int y) {
        pos_.y = y;
    }

    /**
     * @brief Retorna la hitbox actual del rellotge com un rectangle.
     * @return Rect amb la posició i mides del rellotge
     */
    pro2::Rect get_rect() const;

    /**
     * @brief Actualitza l'estat i moviment del rellotge.
     * @param window Finestra on es dibuixa (pot ser útil per col·lisions o altres)
     */
    void update(pro2::Window& window);

    /**
     * @brief Defineix si el sprite del rellotge ha de ser més brillant.
     * @param bright true per activar la brillantor, false per normal
     */
    void set_bright(bool bright) { is_bright_ = bright; }

    /**
     * @brief Activa l'efecte del rellotge, inicialitzant durada i cooldown.
     * @param total_duration Durada total del rellotge (activació + cooldown)
     * @param effect_frames Durada de l'efecte actiu (frames)
     */
    void activate(int total_duration, int effect_frames) {
        is_active_ = true;
        is_in_cooldown_ = true;
        effect_duration_ = effect_frames;
        respawn_delay_ = total_duration - effect_frames;
    }

    /**
     * @brief Indica si el rellotge està en període de cooldown (esperant reapareixer).
     * @return true si està en cooldown
     */
    bool is_in_cooldown() const { return is_in_cooldown_; }

    /**
     * @brief Indica si l'efecte del rellotge està actiu.
     * @return true si està actiu
     */
    bool is_effect_active() const { return is_active_; }

    /**
     * @brief Retorna la durada restant del cooldown o de l'efecte.
     * @return Nombre de frames restants
     */
    int cooldown() const { return effect_duration_; }
};

#endif
