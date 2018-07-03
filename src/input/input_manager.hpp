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
class UiManager;

class InputManager : public InitiableObject {
public:
    void Initialize(AimManager &aim_manager, ActionManager &action_manager, StartScreen &start_screen, UiManager &ui_manager);
    
    /**
     Dispatch the input events based on the turn phase.
     @param turn_phase The current turn phase.
     */
    void Update(TurnPhase turn_phase);
    
    /**
     Dispatch the input events based on the turn phase.
     */
    void UpdateStartScreen();
    
private:
    AimManager *aim_manager_;
    ActionManager *action_manager_;
    StartScreen *start_screen_;
    UiManager *ui_manager_;
    
    TCOD_key_t last_key_;
    TCOD_mouse_t last_mouse_position_;
    
    /**
     Dispatch input events for normal gameplay
     */
    void UpdateNormalMode();
    
    /**
     Dispatch input events for aim mode.
     */
    void UpdateAimMode();
    
    /**
     Dispatch input events for menu mode.
     */
    void UpdateMenuMode();
    
};

#endif /* INPUT_MANAGER_HPP_ */
