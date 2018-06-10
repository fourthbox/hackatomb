#include "player_manager.hpp"

#include "player.hpp"

PlayerManager::PlayerManager() :
player_initialized_ {false} {
}

void PlayerManager::InitializePlayer(std::pair<size_t, size_t> start_position, ActionManager &action_manager, ActorManager &actor_manager, MapsManager &maps_manager) {
    
    auto stats {Stats(5, 5, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 3)};
    
    player_.Initialize(start_position.first,
                        start_position.second,
                        '@',
                        "hero",
                        TCODColor::white,
                        stats);
    
    player_initialized_ = true;
}


Player &PlayerManager::GetPlayer() {
    assert(player_initialized_);
    
    return player_;
}
