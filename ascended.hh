/** @file ascended.hh
 * @brief Especificacions de la classe Ascended
 * 
 *  Aquesta classe representa un escut activable (blessing) que segueix el personatge
 *  principal (Mario) quan és activat. Utilitza una pila per gestionar múltiples blessings.
 */

#ifndef ASCENDED_HH
#define ASCENDED_HH

#include "stack.hh"
#include "geometry.hh"
#include "window.hh"

#ifndef NO_DIAGRAM
#include <vector>
#endif

/**
 * @class Ascended
 * @brief Classe que representa un escut que pot ser activat per protegir el personatge.
 *
 * La classe utilitza una pila per emmagatzemar blessings (escuts). Quan un blessing s’activa,
 * l’escut apareix a la posició del personatge i el segueix mentre està actiu.
 */
class Ascended {
private:
    
    static const std::vector<std::vector<int>> ascended_sprite_;
    
    Stack<int> blessings;  
    bool active = false;
    int duration = 0;
    pro2::Pt pos_;
    
public:
    Ascended() = default;
    
     /**
     * @brief Afegeix un blessing al Stack
     */
    void add_blessing() {
        blessings.push(1);  
    }
    
     /**
     * @brief Retorna si el linked stack esta buit o no
     * 
     * @return Stack buit 
     */
    bool can_activate() const {
        return !blessings.empty();  
    }
    
     /**
     * @brief Retorna si esta o no actiu el blessing
     * 
     * @return Retorna el valor privat active 
     */
    bool is_active() const {
        return active;
    }

    /**
     * @brief Retorna la mida del stack
     */
    int size() const{
        return blessings.size();
    }

    /**
     * @brief Retorna si esta o no actiu el blessing
     * 
     * @param mario_pos la posicio a on ficar l'escut
     */
    void activate(pro2::Pt mario_pos);

    /**
     * @brief Per tenir sempre l'escut on el mario
     * 
     * @param mario_pos la posicio a on s'ha de moure l'escut constantment
     */
    void update(pro2::Pt mario_pos);

    /**
     * @brief Retorna la hitbox de l'objecte
     */
    pro2::Rect get_rect() const;
    
    /**
     * @brief Pinta l'objecte
     * 
     * @param window Finestra on el pinta
     */
    void paint(pro2::Window& window) const;
};

#endif // ASCENDED_HH