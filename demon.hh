/** @file demon.hh
 *  @brief Especificació de la Classe Demon i Fireball
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

/**
 * @class Fireball
 * @brief Classe que representa una bola de foc disparada pel dimoni.
 *
 * Té moviment propi, pot caure o quedar-se en estat actiu un temps limitat.
 * També pot detectar col·lisions mitjançant la seva hitbox.
 */
class Fireball {
 private:
    pro2::Pt pos_;             /**< Posició actual de la bola de foc */
    pro2::Pt speed_;           /**< Velocitat (desplaçament per actualització) */
    bool falling_;             /**< Indica si la bola està caient */
    int duracio_;              /**< Comptador de duració quan el foc està actiu */
    int duracio_fire = 2*48;   /**< Duració total del foc (frames) */

    static const std::vector<std::vector<int>> fireball_sprite_; /**< Sprite per la bola de foc */
    static const std::vector<std::vector<int>> fire_sprite_;     /**< Sprite per el foc actiu */

 public: 
    /** 
     * @brief Constructor per defecte, inicialitza la bola de foc parada i caient.
     */
    Fireball() : pos_({0,0}), speed_({0,0}), falling_(true) {}

    /**
     * @brief Constructor amb posició i velocitat inicial.
     * @param pos Posició inicial de la bola de foc.
     * @param speed Velocitat inicial.
     */
    Fireball(pro2::Pt pos, pro2::Pt speed);

    /**
     * @brief Actualitza l'estat de la bola de foc.
     * 
     * @param window Referència a la finestra per coordenades.
     * @param platforms Conjunt de plataformes per detectar col·lisions.
     */
    void update(pro2::Window& window, const std::set<const Platform*>& platforms);

    /**
     * @brief Dibuixa la bola de foc a la finestra.
     * 
     * @param window Referència a la finestra on es dibuixa.
     */
    void paint(pro2::Window& window) const;

    /**
     * @brief Retorna la posició actual de la bola de foc.
     * @return Posició (pro2::Pt).
     */
    pro2::Pt pos() const {
        return pos_;
    }

    /**
     * @brief Retorna el rectangle que engloba la bola de foc.
     * 
     * @return Un rectangle que correspon a la hitbox de la bola de foc.
     */
    pro2::Rect get_rect() const;

    /**
     * @brief Inicia l'estat de foc actiu a la bola, deixa de caure.
     */
    void start_fire(){
        pos_.y -= 2;
        falling_ = false;
        duracio_ = duracio_fire;
    }

    /**
     * @brief Indica si la bola de foc està caient.
     * 
     * @return true si està caient, false si no.
     */
    bool is_falling() const { return falling_; }

    /**
     * @brief Indica si el foc de la bola ha acabat.
     * 
     * @return true si el foc ja no està actiu, false en cas contrari.
     */
    bool is_expired() const { return !falling_ && duracio_ <= 0; }
    
};


/**
 * @class Demon
 * @brief Classe que modela un dimoni que es mou i dispara boles de foc.
 *
 * El dimoni pot entrar en estat "decayed", canviar la seva velocitat, i gestionar
 * una llista de boles de foc disparades. 
 */
class Demon {

    friend class Fireball;

 private:
    pro2::Pt pos_;                  /**< Posició actual del dimoni */
    pro2::Pt speed_ = {0, 0};      /**< Velocitat actual */
    int fire_cooldown_;             /**< Comptador de cooldown per disparar */
    int fire_rate_;                 /**< Frames entre dispars */
    int fires_per_second_ = 12;          /**< Focs per segon */
    bool is_decayed_ = false;       /**< Estat de decaigut del dimoni */
    List<Fireball> fireballs_;     /**< Llista de boles de foc actives */
    
    int demon_speed_ = 4;           /**< Velocitat del dimoni */

    static const std::vector<std::vector<int>> demon_sprite_;          /**< Sprite del dimoni */
    static const std::vector<std::vector<int>> decayed_demon_sprite_; /**< Sprite del dimoni decaigut */
	
 public:
    /**
     * @brief Constructor per defecte, situa el dimoni a (0,0).
     */
    Demon() : pos_({0,0}), speed_({0,0}), fire_cooldown_(0), fire_rate_(12) {}

    /**
     * @brief Constructor amb posició inicial.
     * @param pos Posició inicial del dimoni.
     */
    Demon(pro2::Pt pos) 
        : pos_(pos), speed_({0, 0}), 
          fire_cooldown_(0), fire_rate_(12) {}

    /**
     * @brief Dibuixa el dimoni a la finestra.
     * @param window Finestra on es dibuixa.
     */
    void paint(pro2::Window& window) const;

    /**
     * @brief Retorna la posició actual del dimoni.
     * 
     * @return Posició (pro2::Pt).
     */
    pro2::Pt pos() const { return pos_; }

    /**
     * @brief Retorna la hitbox del dimoni.
     * 
     * @return Rectangle que representa la hitbox.
     */
    pro2::Rect get_rect() const;

    /**
     * @brief Actualitza el moviment i estat del dimoni.
     * 
     * @param window Finestra on es dibuixa.
     * @param platforms Conjunt de plataformes per detectar col·lisions.
     */
    void update(pro2::Window& window, const std::set<const Platform*>& platforms);
    
    /**
     * @brief Indica si el dimoni ha acabat el cooldown i pot disparar.
     * 
     * @return true si pot disparar, false si encara té cooldown.
     */
    bool should_shoot() const;
    
    /**
     * @brief Reinicia el cooldown per al següent dispar.
     */
    void reset_cooldown(){ fire_cooldown_ = fire_rate_; }

    /**
     * @brief Fica els focs per segon al parametre
     * 
     * @param new_fire_rate Focs per segon que volem
     */
    void set_fire_rate(int new_fire_rate) {
        fire_rate_ = new_fire_rate;
    }

    /**
     * @brief Canvia l'estat del dimoni a decaigut i augmenta la velocitat.
     */
    void decaying(){
        is_decayed_ = true;
        demon_speed_ = 6;
        set_fire_rate(8);
    }

    /**
     * @brief Intenta disparar una nova bola de foc.
     */
    void try_shoot_fireball();

    /**
     * @brief Actualitza totes les boles de foc actives.
     * 
     * @param window Finestra on es dibuixa.
     * @param platforms Plataformes per detectar col·lisions.
     */
    void update_fireballs(pro2::Window& window, const std::set<const Platform*>& platforms);

    /**
     * @brief Comprova si alguna bola de foc col·lisiona amb el Mario o un escut.
     * 
     * @param marioRect Rectangle de Mario.
     * @param ascendedRect Rectangle de l'escut Ascended.
     * 
     * @return true si hi ha col·lisió, false si no.
     */
    bool check_fireball_collisions(const pro2::Rect& marioRect, const pro2::Rect& ascendedRect);
};

#endif
