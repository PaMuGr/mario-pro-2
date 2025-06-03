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
#include "ascended.hh"

/*DEFINICIÓ DE LA CLASSE*/
class Game {
    Mario                 mario_;
    std::vector<Platform> platforms_;
    std::list<Cross> crosses_;
    Sandglass sandglass_;
    Demon demon_;
    pro2::Ascended ascended_;
    std::list<Fireball> fireballs_;
    std::list<Fire> fires_;

    //FINDER de les plataformes i crosses
    Finder<Platform> finder_platforms_;
    Finder<Cross> finder_crosses_;

    bool paused_;
    bool finished_;
    bool reset_;
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

 private:
    static constexpr int sky_blue = 0x5c94fc;
};

#endif