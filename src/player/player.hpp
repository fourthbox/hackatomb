/**
 @file player.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "action_manager.hpp"
#include "actor.hpp"
#include "tile.hpp"

/**
 This class extends Actor with the functionalities that are unique to the player
 */
class Player : public Actor {
public:
    Player();
    
    /**
     Update the player based on the action.
     */
    bool Update(size_t speed) override;
    
    /**
     Set the action the player must perform
     */
    void SetAction(Action action);
                    
private:    
    Action action_;     /**< The action the player must perform this turn */
    void Die() override;
};

#endif /* PLAYER_HPP_ */
