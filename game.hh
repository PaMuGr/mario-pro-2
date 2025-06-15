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

/*DEFINICIÓ DE LA CLASSE*/
class Game {
    Mario                 mario_;
    std::vector<Platform> platforms_;
    Platform still_platform_;
    Mario still_mario_;
    std::list<Cross> crosses_;
    Sandglass sandglass_;
    Demon demon_;
    pro2::Ascended ascended_;
    
    //FINDER de les plataformes i crosses
    Finder<Platform> finder_platforms_;
    Finder<Cross> finder_crosses_;

    bool paused_;

    bool has_time_limit_ = false;
    bool is_dodging_mode_ = false;

    int game_state_ = 0;

    int cross_height_y_ = 0;
    int last_blessed_points_ = 0;
    int crosses_to_get_ = 10; //Crosses al mode facil
    int timer_ = 0;  //Timer per el mode speedrun
    int game_mode_ = 1; //Inicialitzat a Easy

    /**
     * @brief Processa les tecles premudes i actualitza l'estat del joc en conseqüència
     * @param window Finestra principal del joc
     */
    void process_keys(pro2::Window& window);

    /**
     * @brief Actualitza tots els objectes del joc (mario, creus, rellotge, etc.)
     * @param window Finestra principal del joc
     */
    void update_objects(pro2::Window& window);

    /**
     * @brief Mou la càmera seguint la posició del personatge principal
     * @param window Finestra principal del joc
     */
    void update_camera(pro2::Window& window);

 public:

    /**
     * @brief Constructor del joc. Inicialitza els objectes i l'estat inicial
     * @param width Amplada de la finestra
     * @param height Alçada de la finestra
     */
    Game(int width, int height);

    /**
     * @brief Actualitza el joc cada frame
     * @param window Finestra del joc
     */
    void update(pro2::Window& window);

    /**
     * @brief Pinta el joc cada frame
     * @param window Finestra del joc
     */
    void paint(pro2::Window& window);

    /**
     * @brief Retorna un bool segons si el joc esta o no pausat
     * @return True or False segons l'estat del joc
     */
    bool is_paused() const {
        return paused_;
    }

    /**
     * @brief Retorna un bool segons si el joc ha acabat
     * @return True si el jugador ha sortit del joc, fals en cas contrari
     */
    bool is_finished() const {
        return game_state_ == 4;
    }

    /**
     * @brief Retorna un bool segons si el mario ha mort
     * @return True si el mario ha caigut o ha estat colpejat, fals en cas contrari
     */
    bool you_died() const {
        return game_state_ == 5;
    }

    /**
     * @brief Retorna un bool segons si hem guanyat el joc
     * @return True si el jugador ha guanyat, fals en cas contrari
     */
    bool you_won() const {
        return game_state_ == 2;
    }

    /**
     * @brief Canvia el mode de joc al seleccionat
     * @param gamemode Mode de joc al que es jugarà
     */
    void set_gamemode(int gamemode){
        game_mode_ = gamemode;
        apply_game_mode_settings(); 
    }

    /**
     * @brief Actualitza el temporitzador del joc si hi ha límit de temps
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
     * @brief Aplica les configuracions específiquès segons el mode de joc seleccionat
     */
    void apply_game_mode_settings();

    /**
     * @brief Crea un mapa diferent amb plataformes randomitzades per cada reinici del joc
     * @param count Nombre de elements a pantalla a randomitzar
     */
    void generate_level_objects(int count);

    //PAINTING METHODS:

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
     * @brief Centra un text al mitg de la pantalla
     * @param window Finestra on anira el text
     * @param center Mitg de la finestra 
     * @param text Text a pintar
     * @param y_offset Distancia del mitg de la pantalla (útil per més de un text)
     */
    void center_text(pro2::Window& window, pro2::Pt center, const std::string& text, int y_offset);

    //UPDATE METHODS:

    /**
     * @brief Comprova si el mario ha caigut fora de la pantalla
     * @param window Finestra del joc
     * @return True si ha caigut, fals si encara està a la pantalla
     */
    bool check_fallen_off_screen(const pro2::Window& window);

    /**
     * @brief Comprova si mario interactua amb el rellotge i l’activa
     * @param marioRect Rectangle del mario
     */
    void handle_sandglass_interaction(const pro2::Rect& marioRect);

    /**
     * @brief Actualitza l’estat del joc quan el rellotge està activat
     * @param window Finestra del joc
     * @param marioRect Posició del jugador
     */
    void update_time_stoped_mode(pro2::Window& window, const pro2::Rect& marioRect);

    /**
     * @brief Actualitza l’estat normal del joc (sense rellotge)
     * @param window Finestra del joc
     * @param marioRect Posició del jugador
     */
    void update_normal_mode(pro2::Window& window, const pro2::Rect& marioRect);

    /**
     * @brief Actualitza les creus visibles i comprova si han estat recollides
     * @param window Finestra del joc
     * @param marioRect Rectangle del mario
     */
    void update_crosses(pro2::Window& window, const pro2::Rect& marioRect);

    /**
     * @brief Actualitza el comportament del dimoni
     * @param window Finestra del joc
     */
    void update_demon_state(pro2::Window& window);

    /**
     * @brief Comprova si el mario ha aconseguit prou punts per activar benediccions
     */
    void check_blessing_points();

 private:
    static constexpr int sky_blue = 0x5c94fc;
};

#endif