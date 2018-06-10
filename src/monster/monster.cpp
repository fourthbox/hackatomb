#include "monster.hpp"

#include "actor_manager.hpp"
#include "game_constants.hpp"
#include "player.hpp"

#include "game_globals.hpp"

bool Monster::Update(size_t speed, ActionManager &action_manager, MapsManager &maps_manager) {
    assert(initialized_);
    
    if (is_dead_ || !Actor::Update(speed, action_manager, maps_manager))
        return false;
    
    auto player_position {action_manager.SeekPlayer()};
    
    if (player_position == std::experimental::nullopt)
        return false;
    
    auto px {player_position->first};
    auto py {player_position->second};
    
    // Computer fov for the monster
    // and check if the hero is not in range, don't do anything
    if (!maps_manager.IsInFov(*this, px, py))
        return false;
    
    size_t dest_x, dest_y;
    
    // Calculate the next step
    auto success {path_finder_.Walk(dest_x, dest_y, x_, y_, px, py)};
    
    // Check if the moster can move to the specified position
    if (success && action_manager.CanMove(dest_x, dest_y)
        && !action_manager.CanAtttack(dest_x, dest_y)) {
        MoveToPosition(dest_x, dest_y);
        return true;
    } else if (success && action_manager.CanAtttack(dest_x, dest_y)) {
        action_manager.Attack(*this, dest_x, dest_y);
        return true;
    }
    
    return false;
}

void Monster::Initialize(size_t x, size_t y, int const &sprite, std::string const &name, TCODColor const &color, Stats const &stats, ActionManager &action_manager, ActorManager &actor_manager, MapsManager &maps_manager) {
    assert(!initialized_);
    
    is_perma_visible_ = false;
    
    Actor::Initialize(x, y, sprite, name, color, stats);
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
    Actor::Die();
    
    sprite_ = kCharCorpse;
    color_ = kCorpseColor;
}
