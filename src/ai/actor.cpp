#include "actor.hpp"

#include "action_manager.hpp"

using std::string;

void Actor::Initialize(size_t x, size_t y, const int &sprite, std::string name, const TCODColor &color, const Stats &stats, ActionManager &action_manager, MapsManager &maps_manager) {
    assert(!initialized_);
    
    x_ = x;
    y_ = y;
    sprite_ = sprite;
    name_ = name;
    color_ = color;
    stats_ = stats;
    action_manager_ = &action_manager;
    maps_manager_ = &maps_manager;
    
    initialized_ = true;
}

int Actor::GetFovRadius() {
    assert(initialized_);
    
    return stats_.fov_;
}

void Actor::Draw(TCODConsole &console) {
    assert(initialized_);

    console.setChar(x_, y_, sprite_);
    console.setCharForeground(x_, y_, color_);
}

std::pair<size_t, size_t> Actor::GetPosition() {
    assert(initialized_);
    
    return std::make_pair(x_, y_);
}
