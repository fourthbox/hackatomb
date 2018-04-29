#include "input_manager.hpp"

#include "game_constants.hpp"
#include "player.hpp"

void InputManager::Update() {
    assert (player_);

    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &last_key_, &last_mouse_position_, true);
    
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
            player_->maps_manager_->SetAllExplored();
            player_->actor_manager_->SetAllMonstersVisible();
            break;
        default:
            player_->SetAction(Action::NONE_);
            break;
    }
}

void InputManager::UpdateStartScreen() {
    assert (start_screen_);

    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &last_key_, &last_mouse_position_, true);
    
    switch (last_key_.c) {
        case kMoveNorth:
            start_screen_->CycleMenu(0);
            break;
        case kMoveSouth:
            start_screen_->CycleMenu(1);
            break;
        case TCODK_ENTER:
            start_screen_->SelectMenu();
            break;
    }
}
