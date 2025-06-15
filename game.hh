/** @file game.hh
 * @brief Especificació de Funcions del Game
 */

#ifndef GAME_HH
#define GAME_HH

/*INCLUDES*/
#include "mario.hh"
#include "cross.hh"
#include "platform.hh"
#include "window.hh"
#include "utils.hh"
#include "texto.hh"
#include "finder.hh"
#include "sandglass.hh"
#include "demon.hh"
#include "list.hh"
#include "ascended.hh"

#ifndef NO_DIAGRAM
#include <vector>
#endif

/**
 * @class Game
 * @brief Classe principal que gestiona l'estat i la lògica del joc.
 * 
 * La classe Game conté totes les dades i funcionalitats necessàries per controlar
 * el personatge, plataformes, creus, dimoni, temporitzadors, i les diferents pantalles
 * i estats del joc.
 */
class Game {
    Mario                 mario_;               /**< Personatge principal Mario */
    std::vector<Platform> platforms_;           /**< Llista de plataformes al mapa */
    Platform still_platform_;                    /**< Plataforma estàtica per proves o estat */
    Mario still_mario_;                          /**< Mario estàtic per proves o estat */
    std::list<Cross> crosses_;                   /**< Llista de creus per recollir */
    Sandglass sandglass_;                        /**< Objecte rellotge de sorra */
    Demon demon_;                                /**< Dimoni enemic */
    Ascended ascended_;                          /**< Objecte de benedicció activada */
    
    Finder<Platform> finder_platforms_;          /**< Finder per a plataformes */
    Finder<Cross> finder_crosses_;                /**< Finder per a creus */

    bool paused_;                                /**< Estat de pausa del joc */

    bool has_time_limit_ = false;                /**< Indica si el joc té límit de temps */
    bool is_dodging_mode_ = false;               /**< Indica si el mode esquiva està activat */

    int game_state_ = 0;                         /**< Estat actual del joc (menus, jugant, etc.) */

    int cross_height_y_ = 0;                      /**< Alçada de les creus */
    int last_blessed_points_ = 0;                 /**< Últims punts per activar benedicció */
    int crosses_to_get_ = 10;                      /**< Nombre de creus per mode fàcil */
    int timer_ = 0;                               /**< Temporitzador per mode speedrun */
    int game_mode_ = 1;                           /**< Mode de joc actual (ex: 1 = Easy) */

    /**
     * @brief Processa les tecles premudes i actualitza l'estat del joc en conseqüència.
     * @param window Finestra principal del joc
     */
    void process_keys(pro2::Window& window);

    /**
     * @brief Actualitza tots els objectes del joc (Mario, creus, rellotge, etc.)
     * @param window Finestra principal del joc
     */
    void update_objects(pro2::Window& window);

    /**
     * @brief Mou la càmera seguint la posició del personatge principal.
     * @param window Finestra principal del joc
     */
    void update_camera(pro2::Window& window);

public:

    /**
     * @brief Constructor del joc. Inicialitza els objectes i l'estat inicial.
     * @param width Amplada de la finestra
     * @param height Alçada de la finestra
     */
    Game(int width, int height);

    /**
     * @brief Actualitza el joc cada frame.
     * @param window Finestra del joc
     */
    void update(pro2::Window& window);

    /**
     * @brief Pinta el joc cada frame.
     * @param window Finestra del joc
     */
    void paint(pro2::Window& window);

    /**
     * @brief Retorna true si el joc està pausat.
     * @return bool
     */
    bool is_paused() const {
        return paused_;
    }

    /**
     * @brief Retorna true si el joc ha acabat.
     * @return bool
     */
    bool is_finished() const {
        return game_state_ == 4;
    }

    /**
     * @brief Retorna true si Mario ha mort (caigut o colpejat).
     * @return bool
     */
    bool you_died() const {
        return game_state_ == 5;
    }

    /**
     * @brief Retorna true si el jugador ha guanyat.
     * @return bool
     */
    bool you_won() const {
        return game_state_ == 2;
    }

    /**
     * @brief Canvia el mode de joc al seleccionat.
     * @param gamemode Mode de joc al que es jugarà
     */
    void set_gamemode(int gamemode){
        game_mode_ = gamemode;
        apply_game_mode_settings(); 
    }

    /**
     * @brief Actualitza el temporitzador del joc si hi ha límit de temps.
     */
    void update_timer(){
        if (has_time_limit_) {
            timer_--;
            if (timer_ <= 0) {
                game_state_ = 3;  // speedrun ends
            }
        }
    }

    /**
     * @brief Aplica les configuracions específiques segons el mode de joc seleccionat.
     */
    void apply_game_mode_settings();

    /**
     * @brief Crea un mapa diferent amb plataformes randomitzades per cada reinici del joc.
     * @param count Nombre d'elements a pantalla a randomitzar
     */
    void generate_level_objects(int count);

    // Mètodes per pintar objectes:

    /** @brief Pinta les plataformes visibles al mapa */
    void paint_platforms(pro2::Window& window);

    /** @brief Pinta les creus visibles */
    void paint_crosses(pro2::Window& window);

    /** @brief Pinta el dimoni i el seu estat */
    void paint_demon_objects(pro2::Window& window);

    /** @brief Placeholder per pintar boles de foc */
    void paint_fireballs(pro2::Window& window);

    /** @brief Pinta les benediccions i el seu comptador */
    void paint_blessings(pro2::Window& window);

    /** @brief Pinta els punts recollits pel jugador */
    void paint_points(pro2::Window& window);

    /** @brief Mostra la pantalla de pausa */
    void paint_paused_screen(pro2::Window& window);

    /** @brief Mostra la pantalla de game over */
    void paint_gameover_screen(pro2::Window& window);

    /** @brief Mostra la pantalla d'inici del joc */
    void paint_starting_screen(pro2::Window& window);

    /** @brief Mostra la pantalla de victòria */
    void paint_winning_screen(pro2::Window& window);

    /** @brief Mostra la pantalla quan s'acaba el mode speedrun */
    void paint_speedrun_screen(pro2::Window& window);

    /** @brief Dibuixa el marc del joc (recuadre) */
    void paint_game_frame(pro2::Window& window); 

    /** @brief Pinta el temporitzador del joc a la pantalla */
    void paint_timer(pro2::Window& window); 

    /**
     * @brief Centra un text al mitg de la pantalla.
     * @param window Finestra on anirà el text
     * @param center Punt central de la finestra 
     * @param text Text a pintar
     * @param y_offset Desplaçament vertical respecte al centre (per multiples textos)
     */
    void center_text(pro2::Window& window, pro2::Pt center, const std::string& text, int y_offset);

    // Mètodes per actualitzar l'estat:

    /**
     * @brief Comprova si Mario ha caigut fora de la pantalla.
     * @param window Finestra del joc
     * @return True si ha caigut, fals si encara està a la pantalla
     */
    bool check_fallen_off_screen(const pro2::Window& window);

    /**
     * @brief Comprova si Mario interactua amb el rellotge i l’activa.
     * @param marioRect Rectangle de Mario
     */
    void handle_sandglass_interaction(const pro2::Rect& marioRect);

    /**
     * @brief Actualitza l’estat del joc quan el rellotge està activat.
     * @param window Finestra del joc
     * @param marioRect Posició del jugador
     */
    void update_time_stoped_mode(pro2::Window& window, const pro2::Rect& marioRect);

    /**
     * @brief Actualitza l’estat normal del joc (sense rellotge).
     * @param window Finestra del joc
     * @param marioRect Posició del jugador
     */
    void update_normal_mode(pro2::Window& window, const pro2::Rect& marioRect);

    /**
     * @brief Actualitza les creus visibles i comprova si han estat recollides.
     * @param window Finestra del joc
     * @param marioRect Rectangle de Mario
     * @param timestoped Mira si el temps està parat
     */
    void update_crosses(pro2::Window& window, const pro2::Rect& marioRect, bool timestoped);

    /**
     * @brief Actualitza el comportament del dimoni.
     * @param window Finestra del joc
     */
    void update_demon_state(pro2::Window& window);

    /**
     * @brief Comprova si Mario ha aconseguit prou punts per activar benediccions.
     */
    void check_blessing_points();

private:
    static constexpr int sky_blue = 0x5c94fc;  /**< Color blau cel per pintar fons */
};

#endif