/** @file utils.hh
 * @brief Especificacions de les Funcions del Utils
 */

#ifndef UTILS_HH
#define UTILS_HH

#include <vector>
#include "geometry.hh"
#include "window.hh"

namespace pro2 {

/**
 * @brief Dibuja una línea horizontal en la ventana.
 *
 * @param window Ventana en la que se dibuja la línea.
 * @param xini Coordenada x inicial.
 * @param xfin Coordenada x final.
 * @param y Coordenada y.
 * @param color Color de la línea (opcional, si no se pone se asume `white`).
 */
void paint_hline(pro2::Window& window, int xini, int xfin, int y, pro2::Color color = pro2::white);

/**
 * @brief Dibuja una línea vertical en la ventana.
 *
 * @param window Ventana en la que se dibuja la línea.
 * @param x Coordenada x.
 * @param yini Coordenada y inicial.
 * @param yfin Coordenada y final.
 * @param color Color de la línea (opcional, si no se pone se asume `white`).
 */
void paint_vline(pro2::Window& window, int x, int yini, int yfin, pro2::Color color = pro2::white);

/**
 * @brief Dibuixa una imatge/textura a la finestra a partir d'una posició
 *
 * @param window Finestra a la que pintar
 * @param orig   Origen (cantonada de dalt a l'esquerra) del rectangle que forma el _sprite_
 * @param sprite Matriu de colors que representa la imatge (_sprite_).
 * @param mirror Si cal pintar girar la textura horitzontalment
 */
void paint_sprite(pro2::Window&                        window,
                  pro2::Pt                             orig,
                  const std::vector<std::vector<int>>& sprite,
                  bool                                 mirror);


/**
 * @brief Dibuixa una recuadre seguint la càmara
 *
 * @param window Finestra a on ha de pintar
 * @param rect   Rectangle dels tamanys que pintara
 * @param color  Color que utilitzarà per pintar
 * @param size   Gruixuda que tindrà
 */
void paint_empty_rect(pro2::Window& window, pro2::Rect& rect, pro2::Color color, int size);

/**
 * @brief Dibuixa una recuadre seguint la càmara
 *
 * @param window Finestra a on ha de pintar
 * @param rect   Rectangle dels tamanys que pintara
 * @param color  Color que utilitzarà per pintar
 * @param size   Gruixuda que tindrà
 */
void paint_rect(pro2::Window& window, pro2::Rect& rect, pro2::Color color);

/**
 * @brief Mira si una hitbox esta a sobre de l'altre 
 *
 * @param a primera hitbox
 * @param b segona hitbox
 * 
 * @returns Un boolea true or false depen de si interseccions
 */
bool interseccionen(const pro2::Rect& a, const pro2::Rect& b);

/**
 * @brief Retorna un nombre random entre max i min 
 *
 * @param a maxim del rang
 * @param b minim del rang
 * 
 * @returns Un int d'un nombre randomitzat.
 */
int randomizer(int max, int min);

/**
 * @brief Retorna el nombre de digits de num
 *
 * @param num nombre a contar digits
 * 
 * @returns Un int d'el nombre de digits de num
 */
int numDigits(int num);

}

#endif