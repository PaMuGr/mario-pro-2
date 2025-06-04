/** @file game.hh
 * @brief Especificació de Funcions del Game
 */

#ifndef GAME_HH
#define GAME_HH

/*INCLUDES*/
#include <vector>
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
    
    //Llistes usant l'implementació amb punters
    List<Fireball> fireballs_;
    List<Fire> fires_;

    //FINDER de les plataformes i crosses
    Finder<Platform> finder_platforms_;
    Finder<Cross> finder_crosses_;

    bool paused_;
    bool finished_;
    bool reset_;
    bool start_game_;
    int cross_height_y_ = 0;
    int last_blessed_points_ = 0;

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

    //PAINTING METHODS:

    void paint_platforms(pro2::Window& window);
    void paint_crosses(pro2::Window& window);
    void paint_demon_objects(pro2::Window& window);
    void paint_fireballs(pro2::Window& window);
    void paint_blessings(pro2::Window& window);
    void paint_points(pro2::Window& window);
    void paint_paused_screen(pro2::Window& window);
    void paint_gameover_screen(pro2::Window& window);
    //centra un text
    void center_text(pro2::Window& window, pro2::Pt center, const std::string& text, int y_offset);
    void paint_starting_screen(pro2::Window& window);
    void paint_game_frame(pro2::Window& window); 
    
    //UPDATE METHODS:

    bool check_fallen_off_screen(const pro2::Window& window);
    void handle_sandglass_interaction(const pro2::Rect& marioRect);
    void update_time_stoped_mode(pro2::Window& window, const pro2::Rect& marioRect);
    void update_normal_mode(pro2::Window& window, const pro2::Rect& marioRect);
    void try_shoot_fireball();
    void update_fireballs();
    bool check_fireball_hits_platform(Fireball& fireball);
    void update_crosses(pro2::Window& window, const pro2::Rect& marioRect);
    void update_fires();
    void update_fireball_collisions(const pro2::Rect& marioRect, bool timeStoped);
    void update_fire_collisions(const pro2::Rect& marioRect, bool timeStoped);
    void check_blessing_points();
    
 private:
    static constexpr int sky_blue = 0x5c94fc;
};

#endif