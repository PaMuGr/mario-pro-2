/** @file game.hh
 * @brief Especificació de Funcions del Game
 */

#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include "mario.hh"
#include "cross.hh"
#include "platform.hh"
#include "window.hh"
#include "utils.hh"
#include "texto.hh"
#include "finder.hh"

class Game {
    Mario                 mario_;
    std::vector<Platform> platforms_;
    std::list<Cross> crosses_;

    bool paused_;
    bool finished_;
    int cross_height_y_ = 0;
    bool cross_movingup_ = true;

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
     * @brief Retorna un bool segons si el joc esta o no pausat
     * 
     * @return True or False segons l'estat del joc
     */
    bool is_finished() const {
        return finished_;
    }

 private:
    static constexpr int sky_blue = 0x5c94fc;
};

#endif