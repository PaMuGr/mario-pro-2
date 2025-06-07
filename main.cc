/** @file main.cc
 * @brief Mario
 */

/**
 * @mainpage Mario Pro 2 - Documentació del Joc
 * 
 * @section intro_sec Introducció
 * Aquesta és la documentació per el joc de Mario Pro 2, un plataformer 2D amb Jesus com a protagonista
 * - Hi podem trobar les Creus que haurem d'agafar
 * - Enemic -> Dimoni
 * - Un rellotge que para el temps 10 segons
 * 
 * @section tech_sec Detalls Tecnics
 * - Resolució: 480x320 
 * - Target FPS: 48
 * 
 * @section usage_sec Controls del Joc
 * Controls:
 * - Fletxes per moure's (Fletxa d'abaix per baixar plataformes)
 * - Espai per saltar
 * - "B" per utilitzar escut
 * - Si caus o mors, R per reiniciar
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

    cout << endl << "###### MARIO X JESUS ######" << endl;
    cout << "ESCULL LA DIFICULTAT DEL JOC" << endl;
    cout << "1.- FACIL (Agafa 10 crosses)" << endl;
    cout << "2.- INTERMEDI (Agafa 20 crosses)" << endl;
    cout << "3.- DIFICIL (Agafa 40 crosses)" << endl;
    cout << "4.- SPEEDRUN (Amb temps)" << endl;
    cout << "5.- EXIT" << endl;
    cout << "############################" << endl;
    int gamemode;
    cout << endl;
    cout << "Inserta l'opció aqui: ";
    cin >> gamemode;
    cout << endl << "############################" << endl;
    cout << endl;

    if(gamemode != 5){
        cout << "Cargant el joc..." << endl << endl;
        Game game(WIDTH, HEIGHT);
        game.set_gamemode(gamemode);
        cout << "JOC PREPARAT" << endl << endl;
        cout << "############################" << endl << endl;
        while (window.next_frame() && !game.is_finished()) {
            game.update(window);
            game.paint(window);
        } 
    }
}