/**
 * @file platform.hh
 * @brief Definició de la classe Platform que representa plataformes en el joc.
 */

#ifndef PLATFORM_HH
#define PLATFORM_HH

#include "window.hh"

#ifndef NO_DIAGRAM
#include <vector>
#endif

/**
 * @class Platform
 * @brief Representa una plataforma rectangular en el món de joc.
 * 
 * La classe emmagatzema la posició de la plataforma mitjançant coordenades
 * i proporciona funcionalitats per pintar-la, detectar col·lisions i 
 * obtenir la seva hitbox.
 */
class Platform {
 private:
    pro2::Pt topleft_, bottomright_; ///< Vèrtexs superior esquerre i inferior dret (no s'utilitzen al codi actual)
    int left_, right_, top_, bottom_; ///< Coordenades de les vores de la plataforma

    static const std::vector<std::vector<int>> platform_texture_; ///< Sprite o textura de la plataforma

 public:
    /**
     * @brief Constructor per defecte, inicialitza la plataforma buida.
     */
    Platform() : left_(0), right_(0), top_(0), bottom_(0) {}

    /**
     * @brief Constructor còpia.
     * @param other Plataforma a copiar
     */
    Platform(const Platform& other)
        : left_(other.left_), right_(other.right_), top_(other.top_), bottom_(other.bottom_) {}

    /**
     * @brief Constructor que inicialitza les coordenades de la plataforma.
     * @param left Coordinada esquerra
     * @param right Coordinada dreta
     * @param top Coordinada superior
     * @param bottom Coordinada inferior
     */
    Platform(int left, int right, int top, int bottom)
        : left_(left), right_(right), top_(top), bottom_(bottom) {}

    /**
     * @brief Dibuixa la plataforma a la finestra de joc.
     * @param window Finestra on es dibuixa la plataforma
     */
    void paint(pro2::Window& window) const;

    /**
     * @brief Indica si un punt ha travessat la plataforma cap avall entre dos moments.
     * @param plast Posició anterior del punt
     * @param pcurr Posició actual del punt
     * @return true si el punt ha travessat la plataforma cap avall
     */
    bool has_crossed_floor_downwards(pro2::Pt plast, pro2::Pt pcurr) const;

    /**
     * @brief Indica si un punt està dins de la plataforma.
     * @param pt Punt a comprovar
     * @return true si el punt està dins la plataforma
     */
    bool is_pt_inside(pro2::Pt pt) const;

    /**
     * @brief Retorna la coordenada superior de la plataforma.
     * @return Coordenada top
     */
    int top() const {
        return top_;
    }

    /**
     * @brief Modifica la coordenada superior de la plataforma sumant-hi un valor.
     * @param top Increment a sumar a la coordenada top
     */
    void change_top(int top){
        top_ += top;
    }

    /**
     * @brief Retorna la coordenada esquerra de la plataforma.
     * @return Coordenada left
     */
    int left() const { 
        return left_; 
    }
    
    /**
     * @brief Retorna la coordenada dreta de la plataforma.
     * @return Coordenada right
     */
    int right() const { 
        return right_; 
    }

    /**
     * @brief Retorna la coordenada inferior de la plataforma.
     * @return Coordenada bottom
     */
    int bottom() const { 
        return bottom_; 
    }

    /**
     * @brief Modifica la coordenada inferior de la plataforma sumant-hi un valor.
     * @param bottom Increment a sumar a la coordenada bottom
     */
    void change_bottom(int bottom){
        bottom_ += bottom;
    }

    /**
     * @brief Retorna el rectangle que representa la hitbox de la plataforma.
     * @return Rectangular amb la posició de la plataforma
     */
    pro2::Rect get_rect() const {
        return {left_, top_, right_, bottom_};
    }
};

#endif
