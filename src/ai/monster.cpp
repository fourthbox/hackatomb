#include "monster.hpp"

#include "player.hpp"

void Monster::Update() {
    assert(initialized_);
    
    auto px = actor_manager_->GetPlayer()->GetPosition().first;
    auto py = actor_manager_->GetPlayer()->GetPosition().second;
    
    // Computer fov for the monster
    maps_manager_->ComputeFov(shared_from_this());
    
    // If the hero is not in range, don't do anything
    if (!maps_manager_->IsInFov(px, py))
        return;
    
    auto location {path_finder_.Walk(x_, y_, px, py)};
    
    if (location == nullptr)
        return;
    
    x_ = location->first;
    y_ = location->second;
}

void Monster::Initialize(size_t x, size_t y, const int &sprite, std::string name, const TCODColor &color, const Stats &stats, ActionManager_p action_manager, MapsManager_p maps_manager) {
    assert(!initialized_);
    
    is_always_visible_ = false;
    
    Actor::Initialize(x, y, sprite, name, color, stats, action_manager, maps_manager);
    path_finder_.Initialize(maps_manager);
}

bool Monster::IsVisible() {
    assert(initialized_);
    
    return is_always_visible_;
}

void Monster::SetAlwaysVisible(bool is_visible) {
    assert(initialized_);
    
    is_always_visible_ = is_visible;
}
