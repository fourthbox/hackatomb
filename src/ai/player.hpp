/**
 @file player.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "actor.hpp"

/**
 This class extends Actor with the functionalities that are unique to the player
 */
class Player : public Actor {
public:
    Player();

    /**
     Get the field of view for this player.
     @return The field of view.
     */
    int GetFovRadius();
    
    /**
     Update the player based on the action.
     */
    void Update() override;
    
private:
    int fov_radius_;    /**< The field of view of the player */
};

typedef std::shared_ptr<Player> Player_p;

#endif /* PLAYER_HPP_ */
