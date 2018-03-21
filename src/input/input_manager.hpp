/**
 @file input_manager.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef INPUT_MANAGER_HPP_
#define INPUT_MANAGER_HPP_

#include <memory>

#include "initiable_object.hpp"
#include "libtcod.hpp"

class Player;

/**
 */
class InputManager : public InitiableObject {
public:
    void Initialize(std::shared_ptr<Player> player);
    void Update();
    
private:
    std::shared_ptr<Player> player_;
    
    TCOD_key_t last_key_;
    TCOD_mouse_t last_mouse_position_;
    
};

#endif /* INPUT_MANAGER_HPP_ */
