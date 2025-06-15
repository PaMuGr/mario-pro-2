/** @file main.cc
 * @brief Main page of the Mario Game
 */

#ifndef NO_DIAGRAM
#include <vector>
#endif

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
    cout << "5.- DODGING MODE (Sense temps)" << endl;
    cout << "6.- EXIT" << endl;
    cout << "############################" << endl;
    int gamemode;
    cout << endl;
    cout << "Inserta l'opció aqui: ";
    cin >> gamemode;
    cout << endl << "############################" << endl;
    cout << endl;

    if(gamemode != 6){
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