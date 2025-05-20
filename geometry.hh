/** @file geometry.hh
 * @brief Funcions relacionades amb geometria
 */

#ifndef GEOMETRY_HH
#define GEOMETRY_HH

namespace pro2 {

struct Pt {
    int x = 0, y = 0;
};

/**
 * @brief Compara dos punts del pla
 * 
 * La comparació és necessària per poder fer servir `Pt` com la clau d'un `map`.
 * La comparació utilitza primer la coordenada `x` (com si fos més "important"), 
 * i, quan les `x`s són iguals, la coordenada `y`.
 */
inline bool operator<(const Pt& a, const Pt& b) {
    return a.x != b.x ? a.x < b.x : a.y < b.y;
}

/**
 * @brief Compara dos rects del pla
 * 
 * La comparació és necessària per poder fer servir `Rect` com la clau d'un `map`.
 * La comparació utilitza primer la coordenada `x` (com si fos més "important"), 
 * i, quan les `x`s són iguals, la coordenada `y`.
 */
// inline bool operator<(const Rect& a, const Rect& b) {
//     Pt puntA = {a.left, a.top}; //a.left, a.top -> topleft
//     Pt puntB = {b.left, b.top}; //b.left, b.top
//     return puntA < puntB;
// }


struct Rect {
    int left, top, right, bottom;
};

}

#endif