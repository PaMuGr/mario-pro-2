#ifndef BLESSER_HH
#define BLESSER_HH

#include "stack.hh"
#include "ascended.hh"
#include "geometry.hh"
#include "mario.hh"
#include "texto.hh"
#include "utils.hh"

namespace pro2 {

class Blesser {
private:
    Pt pos_;
    Stack<Ascended> shields_;
    Ascended* active_shield_;
    int crosses_collected_;
    const int crosses_needed_ = 5; 

public:
    Blesser(const Pt& pos);
    
    bool activate_shield();        
    bool has_shield() const;       
    
    void update();
    void paint(Window& win) const;
    
    Pt get_pos() const { return pos_; }
};

} // namespace pro2

#endif