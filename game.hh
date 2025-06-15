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

    bool finished_; //state 4
    bool reset_; //state 5
    bool won_; //state 2
    bool speedrun_won_; //state 3
    bool start_game_; //state 0

    bool has_time_limit_ = false;
    bool is_dodging_mode_ = false;

    int game_state_ = 0;

    int cross_height_y_ = 0;
    int last_blessed_points_ = 0;
    int crosses_to_get_ = 10; //Crosses al mode facil
    int timer_ = 0;  //Timer per el mode speedrun
    int game_mode_ = 1; //Inicialitzat a Easy

    void process_keys(pro2::Window& window);
    void update_objects(pro2::Window& window);
    void update_camera(pro2::Window& window);

 public:
    Game(int width, int height);
    void update(pro2::Window& window);
    void paint(pro2::Window& window);

     /**
     * @brief Retorna un bool segons si el joc esta o no pausat
     * 
     * @return True or False segons l'estat del joc
     */
    bool is_paused() const {
        return paused_;
    }

     /**
     * @brief Retorna un bool segons si el joc esta o no finalitzat
     * 
     * @return True or False segons l'estat del joc
     */
    bool is_finished() const {
        return finished_;
    }

     /**
     * @brief Retorna un bool segons si el mario ha mort
     * 
     * @return True or False segons el mario
     */
    bool you_died() const {
        return reset_;
    }

    /**
     * @brief Retorna un bool segons si hem guanyat el joc
     * 
     * @return True or False segons l'estat de joc
     */
    bool you_won() const {
        return won_;
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
     * @brief Actualitza el temps del joc
     */
    void update_timer(){
        if (has_time_limit_) {
            timer_--;
            if (timer_ <= 0) speedrun_won_ = true;
        }
    }

    /**
     * @brief Actualitza l'estat del joc utilitzant switch statements
     */
    void apply_game_mode_settings();

    //PAINTING METHODS:

    /**
     * @brief Pinten els diferents objectes a la finestra
     * 
     * @param window Finestra on es pitaran els diferents objectes i pantalles del joc
     */
    void paint_platforms(pro2::Window& window);
    void paint_crosses(pro2::Window& window);
    void paint_demon_objects(pro2::Window& window);
    void paint_fireballs(pro2::Window& window);
    void paint_blessings(pro2::Window& window);
    void paint_points(pro2::Window& window);
    void paint_paused_screen(pro2::Window& window);
    void paint_gameover_screen(pro2::Window& window);
    void paint_starting_screen(pro2::Window& window);
    void paint_winning_screen(pro2::Window& window);
    void paint_speedrun_screen(pro2::Window& window);
    void paint_game_frame(pro2::Window& window); 
    void paint_timer(pro2::Window& window); 
    

    /**
     * @brief Centra un text al mitg de la pantalla
     * 
     * @param window Finestra on anira el text
     * @param center Mitg de la finestra 
     * @param text Text a pintar
     * @param y_offset Distancia del mitg de la pantalla (útil per més de un text)
     */
    void center_text(pro2::Window& window, pro2::Pt center, const std::string& text, int y_offset);

    
    //UPDATE METHODS:

    bool check_fallen_off_screen(const pro2::Window& window);
    void handle_sandglass_interaction(const pro2::Rect& marioRect);
    void update_time_stoped_mode(pro2::Window& window, const pro2::Rect& marioRect);
    void update_normal_mode(pro2::Window& window, const pro2::Rect& marioRect);
    void update_crosses(pro2::Window& window, const pro2::Rect& marioRect);
    void update_demon_state(pro2::Window& window);
    void check_blessing_points();
    
 private:
    static constexpr int sky_blue = 0x5c94fc;
};

#endif