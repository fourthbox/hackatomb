#include "player.hpp"

#include "game_constants.hpp"
#include "maps_manager.hpp"

Player::Player() {
    assert(!initialized_);
    
    action_ = Action::NONE_;
}

bool Player::Update(size_t speed, ActionManager &action_manager) {
    assert(initialized_);
    
    if (action_manager.GetTurnPhase() == TurnPhase::ACTION_ || !Actor::Update(speed, action_manager))
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
            action_manager.ActionPerformed();
            return false;
            
        default:
            return false;
    }
    
    if (x != 0 || y != 0) {
        auto new_x {x_ + x}, new_y {y_ + y};
        if (action_manager.CanMove(new_x, new_y)
            && !action_manager.CanAtttack(new_x, new_y)) {
            x_ = new_x;
            y_ = new_y;
            action_manager.ActionPerformed();
        } else {
            if (action_manager.PerformAction(*this, new_x, new_y))
                action_manager.ActionPerformed();
        }
    }
    
    return true;
}

void Player::SetAction(Action action) {
    assert(initialized_);

    action_ = action;
}

void Player::Die(ActionManager &action_manager) {
    assert(initialized_);

    action_manager.GameOver();
}
