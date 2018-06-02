#include "input_manager.hpp"

#include "actor_manager.hpp"
#include "game_constants.hpp"

void InputManager::Initialize(ActorManager const &actor_manager, MapsManager &maps_manager, StartScreen &start_screen) {
    assert(!initialized_);
    
    actor_manager_ = &actor_manager;
    maps_manager_ = &maps_manager;
    start_screen_ = &start_screen;
    
    player_ = nullptr;
    
    initialized_ = true;
}

void InputManager::Update() {
    assert (initialized_ && player_ != nullptr);

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
        case kMoveUpstairs:
            if (!last_key_.shift)
                return;
            
            if (auto position {maps_manager_->GetEntrancePosition()}; position && *position == player_->GetPosition()) {
                if (auto new_coors {maps_manager_->MoveToFloor(true)}; position)
                    player_->MoveToPosition(new_coors->first, new_coors->second);
            }
            
            break;
        case kMoveDownstairs:
            if (!last_key_.shift)
                return;

            if (auto position {maps_manager_->GetExitPosition()}; position && *position == player_->GetPosition()) {
                if (auto new_coors {maps_manager_->MoveToFloor(false)}; position)
                    player_->MoveToPosition(new_coors->first, new_coors->second);
            }

            break;
        case 'q':
            maps_manager_->SetAllExplored();
            actor_manager_->SetAllMonstersVisible();
            break;
        default:
            player_->SetAction(Action::NONE_);
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
