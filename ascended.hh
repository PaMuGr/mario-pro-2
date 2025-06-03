// ascended.hh
#ifndef ASCENDED_HH
#define ASCENDED_HH

#include "stack.hh"
#include "geometry.hh"
#include "window.hh"
#include <vector>

namespace pro2 {

class Ascended {
private:
    
    static const std::vector<std::vector<int>> ascended_sprite_;
    
    Stack<int> blessings;  // Using your stack implementation
    bool active = false;
    int duration = 0;
    Pt pos_;
    
public:
    Ascended() = default;
    
    void add_blessing() {
        blessings.push(1);  
    }
    
    bool can_activate() const {
        return !blessings.empty();  
    }
    
    bool is_active() const {
        return active;
    }

    void activate(Pt mario_pos);

    void update(Pt mario_pos);

    Rect get_rect() const;
    
    void paint(Window& window) const;
};

} // namespace pro2

#endif // ASCENDED_HH