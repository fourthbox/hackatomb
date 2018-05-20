#include "player.hpp"

#include "game_constants.hpp"

Player::Player() {
    assert(!initialized_);
    
    action_ = Action::NONE_;
}

void Player::Update() {
    assert(initialized_);
    
    size_t x {0}, y {0};
        
    switch(action_) {
        case Action::MOVE_N_:
            
            y--;
            break;
            
        case Action::MOVE_NE_:
            y--;
            x++;
            break;
            
        case Action::MOVE_E_:
            x++;
            break;
            
        case Action::MOVE_SE_:
            y++;
            x++;
            break;
            
        case Action::MOVE_S_:
            y++;
            break;

        case Action::MOVE_SW_:
            y++;
            x--;
            break;
            
        case Action::MOVE_W_:
            x--;
            break;
            
        case Action::MOVE_NW_:
            y--;
            x--;
            break;
            
        default:
            break;
    }
    
    if (x != 0 || y != 0) {
        if (action_manager_->CanMove(x_ + x, y_ + y)) {
            action_manager_->ActionPerformed();
            x_ += x;
            y_ += y;
        } else if (action_manager_->CanInteract(x_ + x, y_ + y)) {
            action_manager_->Interact(x_ + x, y_ + y);
            action_manager_->ActionPerformed();
        }
    }
}

void Player::SetAction(Action action) {
    assert(initialized_);

    action_ = action;
}
