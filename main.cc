/** @file main.cc
 * @brief Mario
 */

/**
 * @mainpage Mario Pro 2 - Documentació del Joc
 * 
 * @section intro_sec Introducció
 * Aquesta és la documentació per el joc de Mario Pro 2, un plataformer 2D amb Jesus com a protagonista
 * - Hi podem trobar les Creus que haurem d'agafar
 * - Enemic -> Dimoni (Coming soon)
 * - Un rellotge que para el temps 10 segons
 * 
 * @section tech_sec Detalls Tecnics
 * - Resolució: 480x320 
 * - Target FPS: 48
 * 
 * @section usage_sec Controls del Joc
 * Controls:
 * - Fletxer per moure's 
 * - Espai per saltar
 * - Si caus torna a començar desde 0 el joc, no cal reiniciar
 */

#include <vector>
#include "game.hh"
#include "window.hh"

using namespace std;

const int WIDTH = 480, HEIGHT = 320;
const int ZOOM = 2;
const int FPS = 48;

int main() {
    srand(time(0));
    
    pro2::Window window("Mario Pro 2", WIDTH, HEIGHT, ZOOM);
    window.set_fps(FPS);

    Game game(WIDTH, HEIGHT);

    while (window.next_frame() && !game.is_finished()) {
        game.update(window);
        game.paint(window);
    } 
}