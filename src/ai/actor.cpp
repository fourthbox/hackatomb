#include "actor.hpp"

using std::string;

void Actor::Initialize(size_t x, size_t y, const int &sprite, std::string &name, const TCODColor &color, const Stats &stats, std::shared_ptr<ActionManager> action_manager) {
    assert(!initialized_);
    
    x_ = x;
    y_ = y;
    sprite_ = sprite;
    name_ = name;
    color_ = color;
    stats_ = stats;
    action_manager_ = action_manager;
    
    initialized_ = true;
}

void Actor::Draw(std::shared_ptr<TCODConsole> console) {
    assert(initialized_);

    console->setChar(x_, y_, sprite_);
    console->setCharForeground(x_, y_, color_);
}

libpmg::Location Actor::GetPosition() {
    assert(initialized_);
    
    return libpmg::Location(x_, y_);
}

//size_t Actor::GetAtk() {
//    return stats_.atk_;
//}
//
//size_t Actor::GetDef() {
//    return stats_.def_;
//}
//
//void Actor::ApplyDmg(size_t dmg) {
//    stats_.current_hp_ -= dmg;
//
//    if (stats_.current_hp_ <= 0)
//        Die();
//}
//
//void Actor::Die() {
//    sprite_ = '%';
//    color_ = TCODColor::darkRed;
//}

