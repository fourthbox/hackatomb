#ifndef PLAYER_MANAGER_HPP_
#define PLAYER_MANAGER_HPP_

#include <memory>

#include "player.hpp"

class PlayerManager {
public:
    PlayerManager();
    void InitializePlayer(std::pair<size_t, size_t> start_position, ActionManager *action_manager, MapsManager* maps_manager);
    Player &GetPlayer();
    
private:
    Player player_;
    bool player_initialized_;
    
};

#endif /* PLAYER_MANAGER_HPP_ */
