/** @file ascended.hh
 * @brief Especificacions de la classe Ascended
 */

#ifndef ASCENDED_HH
#define ASCENDED_HH

#include "stack.hh"
#include "geometry.hh"
#include "window.hh"

#ifndef NO_DIAGRAM
#include <vector>
#endif

namespace pro2 {

class Ascended {
private:
    
    static const std::vector<std::vector<int>> ascended_sprite_;
    
    Stack<int> blessings;  
    bool active = false;
    int duration = 0;
    Pt pos_;
    
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
    void activate(Pt mario_pos);

    /**
     * @brief Per tenir sempre l'escut on el mario
     * 
     * @param mario_pos la posicio a on s'ha de moure l'escut constantment
     */
    void update(Pt mario_pos);

    /**
     * @brief Retorna la hitbox de l'objecte
     */
    Rect get_rect() const;
    
    /**
     * @brief Pinta l'objecte
     * 
     * @param window Finestra on el pinta
     */
    void paint(Window& window) const;
};

} // namespace pro2

#endif // ASCENDED_HH