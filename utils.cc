/** @file utils.cc
 * @brief Funcions del Utils relacionat amb utilitats generals
 */

#include "utils.hh"
using namespace std;

namespace pro2 {

void paint_hline(pro2::Window& window, int xini, int xfin, int y, Color color) {
    for (int x = xini; x <= xfin; x++) {
        window.set_pixel({x, y}, color);
    }
}

void paint_vline(pro2::Window& window, int x, int yini, int yfin, Color color) {
    for (int y = yini; y <= yfin; y++) {
        window.set_pixel({x, y}, color);
    }
}

void paint_sprite(pro2::Window&              window,
                  pro2::Pt                   orig,
                  const vector<vector<int>>& sprite,
                  bool                       mirror) {
    for (int i = 0; i < sprite.size(); i++) {
        const vector<int>& line = sprite[i];
        for (int j = 0; j < line.size(); j++) {
            const int _j = mirror ? line.size() - j - 1 : j;
            if (line[_j] >= 0) {
                window.set_pixel({orig.x + j, orig.y + i}, line[_j]);
            }
        }
    }
}

void paint_empty_rect(pro2::Window& window, pro2::Rect& rect, pro2::Color color, int size){
    //Top Line
    for(int i = 0; i < size; i++){
        paint_hline(window, rect.left, rect.right, rect.top + i, color);
    }
    
    //Bottom Line
    for(int i = 0; i < size; i++){
        paint_hline(window, rect.left, rect.right, rect.bottom - 1 - i, color);
    }
    //Left Line
    for(int i = 0; i < size; i++){
        paint_vline(window, rect.left + i, rect.top, rect.bottom, color);
    }
    //Right Line
    for(int i = 0; i < size; i++){
        paint_vline(window, rect.right - 1 - i, rect.top, rect.bottom, color);
    }
} 

void paint_rect(pro2::Window& window, pro2::Rect& rect, pro2::Color color){
    for(int x = rect.left; x <= rect.right; x++){
        for(int y = rect.top; y < rect.bottom; y++){
            paint_vline(window, x, rect.top, rect.bottom, color);
        }
    }
}

bool interseccionen(const pro2::Rect& a, const pro2::Rect& b){
    return !(a.right < b.left || a.left > b.right || a.bottom < b.top || a.top > b.bottom);
}

int randomizer(int max, int min){
    int range = max - min;
    return rand() % range + min;
}

int numDigits(int num){
    if (num == 0) return 1; 
    int count = 0;
    while (num != 0) {
        num /= 10; 
        count++;
    }
    return count;
}

}  // namespace pro2