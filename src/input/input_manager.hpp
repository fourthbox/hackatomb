/**
 @file input_manager.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef INPUT_MANAGER_HPP_
#define INPUT_MANAGER_HPP_

#include <memory>

#include "action_manager.hpp"
#include "libtcod.hpp"
#include "start_screen.hpp"

class Player;

/**
 */
class InputManager {
public:
    void Update();
    void UpdateStartScreen();
    
    inline void SetPlayer(std::shared_ptr<Player> player) { player_ = player; }
    inline void SetStartScreen(std::shared_ptr<StartScreen> start_screen) { start_screen_ = start_screen; }
    
private:
    std::shared_ptr<Player> player_;
    std::shared_ptr<StartScreen> start_screen_;
    
    TCOD_key_t last_key_;
    TCOD_mouse_t last_mouse_position_;
    
};

#endif /* INPUT_MANAGER_HPP_ */
