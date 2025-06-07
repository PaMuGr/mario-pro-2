/** @file texto.hh
 * @brief Especificació de les Funcions del Text
 */

#ifndef  TEXT_HH
#define TEXT_HH
#include "utils.hh"
#include "window.hh"
#include <vector>
#include <map>
#include <list>

/**
 * @brief Pinta un sol digit
 *
 * @param window Finestra on pintarem
 * @param pos Posició x i y on pintar el digit
 * @param digit Digit a pintar
 * 
 */
void paint_digit(pro2::Window& window, pro2::Pt pos, int digit);

/**
 * @brief Pinta una sola lletra
 *
 * @param window Finestra on pintarem
 * @param pos Posició x i y on pintar el digit
 * @param letter Lletra a pintar
 * 
 */
void paint_letter( pro2::Window& window, pro2::Pt pos, char letter);

/**
 * @brief Pinta un nombre
 *
 * @param window Finestra on pintarem
 * @param pos Posició x i y on pintar el digit
 * @param number Numero a pintar
 * @param color Color del text a pintar
 * 
 */
void paint_number(pro2::Window& window, pro2::Pt pos, int  number);

/**
 * @brief Pinta un text
 *
 * @param window Finestra on pintarem
 * @param pos Posició x i y on pintar el digit
 * @param text Text a pintar
 * @param color Color del text a pintar
 * 
 */
void paint_text(pro2::Window& window, pro2::Pt pos, const std::string& text);

#endif
