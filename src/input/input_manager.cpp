#include "input_manager.hpp"

#include "aim_manager.hpp"
#include "game_constants.hpp"
#include "start_screen.hpp"

void InputManager::Initialize(AimManager &aim_manager, ActionManager &action_manager, StartScreen &start_screen) {
    assert(!initialized_);
    
    this->aim_manager_ = &aim_manager;
    this->action_manager_ = &action_manager;
    this->start_screen_ = &start_screen;
    
    initialized_ = true;
}

void InputManager::Update(TurnPhase turn_phase) {
    assert (initialized_);
    
    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &last_key_, &last_mouse_position_, true);

    switch (turn_phase) {
        case TurnPhase::IDLE_:
            UpdateNormalMode();
            break;
        case TurnPhase::AIM_:
            UpdateAimMode();
            break;
        default:
            break;
    }
}

void InputManager::UpdateNormalMode() {
    // SHIFT + keys
    if (last_key_.shift) {
        switch (last_key_.c) {
            case kMoveUpstairs:
                action_manager_->MoveUpstairs();
                
                break;
            case kMoveDownstairs:
                action_manager_->MoveDowstairs();
                
                break;
            default:
                action_manager_->DoNothing();
                break;
        }
        
    } else {
        // Normal keys
        switch (last_key_.c) {
            case kMoveNorth:
                action_manager_->PlayerAction(Action::MOVE_N_);
                break;
            case kMoveNorthEast:
                action_manager_->PlayerAction(Action::MOVE_NE_);
                break;
            case kMoveEast:
                action_manager_->PlayerAction(Action::MOVE_E_);
                break;
            case kMoveSouthEast:
                action_manager_->PlayerAction(Action::MOVE_SE_);
                break;
            case kMoveSouth:
                action_manager_->PlayerAction(Action::MOVE_S_);
                break;
            case kMoveSouthWest:
                action_manager_->PlayerAction(Action::MOVE_SW_);
                break;
            case kMoveWest:
                action_manager_->PlayerAction(Action::MOVE_W_);
                break;
            case kMoveNorthWest:
                action_manager_->PlayerAction(Action::MOVE_NW_);
                break;
            case 'q':
                action_manager_->PerformFloorMapping();
                break;
            case kSkipTurn:
                action_manager_->PlayerAction(Action::SKIP);
                break;
            case kEnterAimMode:
                // Setup aim mode turn phase
                action_manager_->StartAiming();
                break;
            default:
                action_manager_->PlayerAction(Action::NONE_);
                break;
        }
    }
}

void InputManager::UpdateAimMode() {
    
    // Check for enter keys
    switch (last_key_.vk) {
        case kSelectOption:
            action_manager_->PerformActionOnCrosshair();
            action_manager_->PlayerAction(Action::NONE_);
            return;
        default:
            break;
    }

    switch (last_key_.c) {
        case kMoveNorth:
            aim_manager_->SetAction(Action::MOVE_N_);
            break;
        case kMoveNorthEast:
            aim_manager_->SetAction(Action::MOVE_NE_);
            break;
        case kMoveEast:
            aim_manager_->SetAction(Action::MOVE_E_);
            break;
        case kMoveSouthEast:
            aim_manager_->SetAction(Action::MOVE_SE_);
            break;
        case kMoveSouth:
            aim_manager_->SetAction(Action::MOVE_S_);
            break;
        case kMoveSouthWest:
            aim_manager_->SetAction(Action::MOVE_SW_);
            break;
        case kMoveWest:
            aim_manager_->SetAction(Action::MOVE_W_);
            break;
        case kMoveNorthWest:
            aim_manager_->SetAction(Action::MOVE_NW_);
            break;
        default:
            aim_manager_->SetAction(Action::NONE_);
            break;
    }
}

void InputManager::UpdateStartScreen() {
    assert (initialized_);

    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &last_key_, &last_mouse_position_, true);
    
    start_screen_->TriggerCommand(last_key_.c);
}
