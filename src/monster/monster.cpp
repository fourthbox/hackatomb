#include "monster.hpp"

#include "actor_manager.hpp"
#include "game_constants.hpp"
#include "player.hpp"

#include "game_globals.hpp"

bool Monster::Update(size_t speed, ActionManager &action_manager, MapsManager &maps_manager) {
    assert(initialized_);
    assert(map_location_);
    
    if (is_dead_ || !Actor::Update(speed, action_manager, maps_manager))
        return false;
        
    auto player_location {action_manager.SeekPlayer()};
    
    if (!player_location)
        return false;
    
    // Compute fov for the monster
    // and check if the hero is not in range, don't do anything
    if (!maps_manager.IsInFov(*this, *player_location))
        return false;
    
    size_t dest_x, dest_y;
    
    // Calculate the next step
    auto success {path_finder_.Walk(dest_x, dest_y,
                                    *map_location_,
                                    *player_location)};
    
    // Create destination map location
    MapLocation destination (map_location_->dungeon_category_, map_location_->floor_, dest_x, dest_y);
    
    // Check if the moster can move to the specified position
    if (success && action_manager.CanMove(destination)
        && !action_manager.CanAtttack(destination)) {
        MoveToLocation(destination);
        return true;
    } else if (success && action_manager.CanAtttack(destination)) {
        action_manager.Attack(*this, destination);
        return true;
    }
    
    return false;
}

void Monster::Initialize(MapLocation const &map_location, MonsterStats const &stats, MapsManager &maps_manager) {
    assert(!initialized_);
    
    is_perma_visible_ = false;
    
    Actor::Initialize(map_location, stats.sprite_, stats.name_, stats.color_, stats);
    
    // Initialize the pathfinder, if possible
    if (maps_manager.IsFloorLoaded(map_location))
        path_finder_.Initialize(map_location.dungeon_category_, map_location.floor_, maps_manager);
}

bool Monster::IsPermaVisible() {
    assert(initialized_);
    
    return is_perma_visible_;
}

void Monster::TogglePermaVisible(bool is_perma_visible) {
    assert(initialized_);
    
    is_perma_visible_ = is_perma_visible;
}

void Monster::Die() {
    Actor::Die();
    
    sprite_ = kCharCorpse;
    color_ = kCorpseColor;
}

void Monster::LoadIntoLocation(MapLocation const &location, MapsManager &maps_manager) {
    assert(map_location_);
    
    // Initialize the pathfinder
    path_finder_.Initialize(location.dungeon_category_, location.floor_, maps_manager);

    Actor::MoveToLocation(location);
}
