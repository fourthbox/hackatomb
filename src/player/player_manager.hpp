#ifndef PLAYER_MANAGER_HPP_
#define PLAYER_MANAGER_HPP_

#include "player.hpp"

class PlayerManager {
public:
    PlayerManager();
    void InitializePlayer(MapLocation const &start_position);
    Player &GetPlayer();
        
private:
    Player player_;
    bool player_initialized_;    
};

#endif /* PLAYER_MANAGER_HPP_ */
