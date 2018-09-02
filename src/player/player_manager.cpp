#include "player_manager.hpp"

#include "player.hpp"
#include "game_constants.hpp"

PlayerManager::PlayerManager() :
player_initialized_ {false} {
}

void PlayerManager::InitializePlayer(MapLocation const &start_position) {
    
    auto stats {Stats(1, 5, 5, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 3)};
    
    player_.Initialize(start_position,
                       kCharHuman,
                       "hero",
                       TCODColor::white,
                       stats);

    player_initialized_ = true;
}


Player &PlayerManager::GetPlayer() {
    assert(player_initialized_);
    
    return player_;
}
