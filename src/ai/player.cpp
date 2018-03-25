#include "player.hpp"

#include "game_constants.hpp"

Player::Player() :
fov_radius_ {kDefaultFovRadius} {
    assert(!initialized_);
    
    action_ = Action::NONE;
}

void Player::Update() {
    assert(initialized_);
    
    size_t x {0};
    size_t y {0};
        
    switch(action_) {
        case Action::MOVE_N:
            y--;
            break;
            
        case Action::MOVE_NE:
            y--;
            x++;
            break;
            
        case Action::MOVE_E:
            x++;
            break;
            
        case Action::MOVE_SE:
            y++;
            x++;
            break;
            
        case Action::MOVE_S:
            y++;
            break;

        case Action::MOVE_SW:
            y++;
            x--;
            break;
            
        case Action::MOVE_W:
            x--;
            break;
            
        case Action::MOVE_NW:
            y--;
            x--;
            break;
            
        default:
            break;
    }
    
    if (x != 0 || y != 0) {
        if (action_manager_->CanMove(x_ + x, y_ + y)) {
            action_manager_->Moved();
            x_ += x;
            y_ += y;
        }
    }
}

void Player::SetAction(Action action) {
    assert(initialized_);

    action_ = action;
}
