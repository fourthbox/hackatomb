#include "monster.hpp"

#include "actor_manager.hpp"
#include "player.hpp"

void Monster::Update() {
    assert(initialized_);
    
    auto px = actor_manager_->GetPlayer().GetPosition().first;
    auto py = actor_manager_->GetPlayer().GetPosition().second;
    
    // Computer fov for the monster
    maps_manager_->ComputeFov(this);
    
    // If the hero is not in range, don't do anything
    if (!maps_manager_->IsInFov(px, py))
        return;
    
    auto success {path_finder_.Walk(x_, y_, x_, y_, px, py)};
    
}

void Monster::Initialize(size_t x, size_t y, const int &sprite, std::string name, const TCODColor &color, const Stats &stats, ActionManager *action_manager, MapsManager *maps_manager) {
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
