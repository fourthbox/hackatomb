/**
 @file input_manager.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef INPUT_MANAGER_HPP_
#define INPUT_MANAGER_HPP_

#include "action_manager.hpp"
#include "libtcod.hpp"
#include "start_screen.hpp"

class Player;

/**
 */
class InputManager : public InitiableObject {
public:
    void Initialize(ActorManager const &actor_manager, MapsManager &maps_manager, StartScreen &start_screen);
    
    void Update();
    
    void UpdateStartScreen();
    
    inline void SetPlayer(Player &player) { player_ = &player; }
    
private:
    Player *player_;
    StartScreen *start_screen_;
    MapsManager *maps_manager_;
    const ActorManager *actor_manager_;
    
    TCOD_key_t last_key_;
    TCOD_mouse_t last_mouse_position_;
    
};

#endif /* INPUT_MANAGER_HPP_ */
