#ifndef ASCENDED_HH
#define ASCENDED_HH

#include "geometry.hh"
#include "window.hh"
#include <vector>

namespace pro2 {

class Ascended {
private:
    Pt pos_;
    bool active_;
    int duration_;
    static const std::vector<std::vector<int>> ascended_sprite_;

public:
    Ascended(const Pt& pos = {0, 0}, int duration = 180); // 3 seconds at 60fps
    
    void activate(const Pt& pos, int duration);
    void update();
    void paint(Window& window) const;
    Rect get_rect() const;
    
    bool is_active() const { return active_; }
};

} // namespace pro2

#endif