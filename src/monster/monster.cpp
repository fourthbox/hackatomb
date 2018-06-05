#include "monster.hpp"

#include "actor_manager.hpp"
#include "game_constants.hpp"
#include "player.hpp"

#include "game_globals.hpp"

bool Monster::Update(size_t speed) {
    assert(initialized_);
    
    if (is_dead_ || !Actor::Update(speed))
        return false;
    
    auto px {actor_manager_->GetPlayer().GetPosition().first};
    auto py {actor_manager_->GetPlayer().GetPosition().second};
    
    // Computer fov for the monster
    maps_manager_->ComputeFov(*this);
    
    // If the hero is not in range, don't do anything
    if (!maps_manager_->IsInFov(px, py))
        return false;
    
    size_t dest_x, dest_y;
    
    // Calculate the next step
    auto success {path_finder_.Walk(dest_x, dest_y, x_, y_, px, py)};
    
    // Check if the moster can move to the specified position
    if (success && action_manager_->CanMove(dest_x, dest_y)
        && !action_manager_->CanAtttack(dest_x, dest_y)) {
        x_ = dest_x;
        y_ = dest_y;
        
        return true;
    } else if (success && action_manager_->CanAtttack(dest_x, dest_y)) {
        action_manager_->Attack(*this, dest_x, dest_y);
        return true;
    }
    
    return false;
}

void Monster::Initialize(size_t x, size_t y, int const &sprite, std::string const &name, TCODColor const &color, Stats const &stats, ActionManager &action_manager, ActorManager &actor_manager, MapsManager &maps_manager) {
    assert(!initialized_);
    
    is_perma_visible_ = false;
    
    Actor::Initialize(x, y, sprite, name, color, stats, action_manager, actor_manager, maps_manager);
    path_finder_.Initialize(maps_manager);
}

bool Monster::IsPermaVisible() {
    assert(initialized_);
    
    return is_perma_visible_;
}

void Monster::SetPermaVisible(bool is_perma_visible) {
    assert(initialized_);
    
    is_perma_visible_ = is_perma_visible;
}

void Monster::Die() {
    sprite_ = kCharCorpse;
    color_ = kCorpseColor;
    
    is_dead_ = true;
}
