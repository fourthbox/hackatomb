#include "input_manager.hpp"

#include "actor_manager.hpp"
#include "game_constants.hpp"

void InputManager::Initialize(ActorManager const &actor_manager, MapsManager &maps_manager, StartScreen &start_screen, AimManager &aim_manager, ActionManager &action_manager) {
    assert(!initialized_);
    
    actor_manager_ = &actor_manager;
    maps_manager_ = &maps_manager;
    start_screen_ = &start_screen;
    aim_manager_ = &aim_manager;
    action_manager_ = &action_manager;
    
    player_ = nullptr;
    
    initialized_ = true;
}

void InputManager::Update() {
    assert (initialized_ && player_ != nullptr && action_manager_->GetTurnPhase() != TurnPhase::ACTION_);
    
    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &last_key_, &last_mouse_position_, true);

    switch (action_manager_->GetTurnPhase()) {
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
                if (auto position {maps_manager_->GetEntrancePosition()}; position && *position == player_->GetPosition()) {
                    if (auto new_coors {maps_manager_->MoveToFloor(true)}; position)
                        player_->MoveToPosition(new_coors->first, new_coors->second);
                }
                
                break;
            case kMoveDownstairs:
                if (auto position {maps_manager_->GetExitPosition()}; position && *position == player_->GetPosition()) {
                    if (auto new_coors {maps_manager_->MoveToFloor(false)}; position)
                        player_->MoveToPosition(new_coors->first, new_coors->second);
                }
                
                break;
            default:
                player_->SetAction(Action::NONE_);
                break;
        }
        
    } else {
        // Normal keys
        switch (last_key_.c) {
            case kMoveNorth:
                player_->SetAction(Action::MOVE_N_);
                break;
            case kMoveNorthEast:
                player_->SetAction(Action::MOVE_NE_);
                break;
            case kMoveEast:
                player_->SetAction(Action::MOVE_E_);
                break;
            case kMoveSouthEast:
                player_->SetAction(Action::MOVE_SE_);
                break;
            case kMoveSouth:
                player_->SetAction(Action::MOVE_S_);
                break;
            case kMoveSouthWest:
                player_->SetAction(Action::MOVE_SW_);
                break;
            case kMoveWest:
                player_->SetAction(Action::MOVE_W_);
                break;
            case kMoveNorthWest:
                player_->SetAction(Action::MOVE_NW_);
                break;
            case 'q':
                maps_manager_->SetAllExplored();
                actor_manager_->SetAllMonstersVisible();
                break;
            case kSkipTurn:
                player_->SetAction(Action::SKIP);
                break;
            case kEnterAimMode:
                // Setup aim mode turn phase
                action_manager_->SwitchToAimMode();
                
                // Setup crosshair for arrows
                aim_manager_->SetupCrossshair(CrosshairMode::ARROW_, player_->GetFovRadius());
                
                // Set default player action
                player_->SetAction(Action::NONE_);
                break;
            default:
                player_->SetAction(Action::NONE_);
                break;
        }
    }
}

void InputManager::UpdateAimMode() {
    
    // Check for enter keys
    switch (last_key_.vk) {
        case kSelectOption:
            aim_manager_->PerformActionOnCrosshair();
            
            aim_manager_->ResetCrosshair();
            
            action_manager_->ActionPerformed();
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
    
    switch (last_key_.c) {
        case kMoveNorth:
            start_screen_->CycleMenu(0);
            return;
        case kMoveSouth:
            start_screen_->CycleMenu(1);
            return;
    }
    
    switch (last_key_.vk) {
        case TCODK_ENTER:
            start_screen_->SelectMenu();
            return;
    }

}
