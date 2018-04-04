#include "input_manager.hpp"

#include "game_constants.hpp"
#include "player.hpp"

void InputManager::Initialize(Player_p player) {
    assert(!initialized_);
    
    player_ = player;
    
    initialized_ = true;
}

void InputManager::Update() {
    assert(initialized_);
    
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS|TCOD_EVENT_MOUSE, &last_key_, &last_mouse_position_);
    
    switch (last_key_.c) {
        case kMoveNorth:
            player_->SetAction(Action::MOVE_N);
            break;
        case kMoveNorthEast:
            player_->SetAction(Action::MOVE_NE);
            break;
        case kMoveEast:
            player_->SetAction(Action::MOVE_E);
            break;
        case kMoveSouthEast:
            player_->SetAction(Action::MOVE_SE);
            break;
        case kMoveSouth:
            player_->SetAction(Action::MOVE_S);
            break;
        case kMoveSouthWest:
            player_->SetAction(Action::MOVE_SW);
            break;
        case kMoveWest:
            player_->SetAction(Action::MOVE_W);
            break;
        case kMoveNorthWest:
            player_->SetAction(Action::MOVE_NW);
            break;
        case 'q':
            player_->maps_manager_->SetAllExplored();
            player_->actor_manager_->SetAllMonstersVisible();
            break;
        default:
            player_->SetAction(Action::NONE);
            break;
    }

}
