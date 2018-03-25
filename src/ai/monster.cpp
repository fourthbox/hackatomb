#include "monster.hpp"

#include "player.hpp"

void Monster::Update() {
    assert(initialized_);
    
    auto location {path_finder_.Walk(x_,
                                     y_,
                                     actor_manager_->GetPlayer()->GetPosition().first,
                                     actor_manager_->GetPlayer()->GetPosition().second)};
    
    if (location == nullptr)
        return;
    
    x_ = location->first;
    y_ = location->second;
}

void Monster::Initialize(size_t x, size_t y, const int &sprite, std::string &name, const TCODColor &color, const Stats &stats, ActionManager_p action_manager, MapsManager_p maps_manager) {
    assert(!initialized_);
    
    Actor::Initialize(x, y, sprite, name, color, stats, action_manager, maps_manager);
    path_finder_.Initialize(maps_manager);
}
