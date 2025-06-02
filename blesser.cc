#include "blesser.hh"

using namespace pro2;

Blesser::Blesser(const Pt& pos) 
    : pos_(pos), crosses_collected_(0), active_shield_(nullptr) {}

bool Blesser::activate_shield() {
    if (!shields_.empty() && !active_shield_) {
        active_shield_ = &shields_.top();
        active_shield_->activate(pos_, 180);
        shields_.pop();
        return true;
    }
    return false;
}

bool Blesser::has_shield() const {
    return !shields_.empty();
}

void Blesser::update() {
    // Update position if needed
}

void Blesser::paint(Window& window) const {
    if (!shields_.empty()) {
        paint_number(window, {pos_.x, pos_.y - 20}, shields_.size());
    }
}
