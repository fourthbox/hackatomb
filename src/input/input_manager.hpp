/**
 @file input_manager.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef INPUT_MANAGER_HPP_
#define INPUT_MANAGER_HPP_

#include "action_manager.hpp"
#include "initiable_object.hpp"
#include "libtcod.hpp"
#include "turn_manager.hpp"

class AimManager;
class StartScreen;

class InputManager : public InitiableObject {
public:
    void Initialize(AimManager &aim_manager, ActionManager &action_manager, StartScreen &start_screen);
    
    void Update(TurnPhase turn_phase);
    
    void UpdateStartScreen();
    
private:
    AimManager *aim_manager_;
    ActionManager *action_manager_;
    StartScreen *start_screen_;
    
    TCOD_key_t last_key_;
    TCOD_mouse_t last_mouse_position_;
    
    void UpdateNormalMode();
    void UpdateAimMode();
    
};

#endif /* INPUT_MANAGER_HPP_ */
