#include "player.hpp"

#include "game_constants.hpp"

Player::Player() {
    assert(!initialized_);
    
    action_ = Action::NONE_;
}

bool Player::Update(size_t speed) {
    assert(initialized_);
    
    if (!Actor::Update(speed))
        return false;

    int x {0}, y {0};
        
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
            
        case Action::SKIP:
            action_manager_->ActionPerformed();
            return false;
            
        default:
            return false;
    }
    
    if (x != 0 || y != 0) {
        if (action_manager_->CanMove(x_ + x, y_ + y)) {
            x_ += x;
            y_ += y;
            action_manager_->ActionPerformed();
        } else {
            if (action_manager_->PerformAction(*this, x_ + x, y_ + y))
                action_manager_->ActionPerformed();
        }
    }
    
    return true;
}

void Player::SetAction(Action action) {
    assert(initialized_);

    action_ = action;
}

void Player::Die() {
    assert(initialized_);

    action_manager_->GameOver();
}
