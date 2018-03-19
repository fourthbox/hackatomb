#include "player.hpp"

#include "action_manager.hpp"
#include "game_constants.hpp"
#include "key_mapper.hpp"

Player::Player() :
fov_radius_ {kDefaultFovRadius} {
    assert(!initialized_);
}

void Player::Update() {
    assert(initialized_);
    
    auto action { KeyMapper::GetActionByKey() };
    size_t x {0};
    size_t y {0};
        
    switch(action) {
        case KeyMapper::Action::MOVE_N:
            y--;
            break;
            
        case KeyMapper::Action::MOVE_NE:
            y--;
            x++;
            break;
            
        case KeyMapper::Action::MOVE_E:
            x++;
            break;
            
        case KeyMapper::Action::MOVE_SE:
            y++;
            x++;
            break;
            
        case KeyMapper::Action::MOVE_S:
            y++;
            break;

        case KeyMapper::Action::MOVE_SW:
            y++;
            x--;
            break;
            
        case KeyMapper::Action::MOVE_W:
            x--;
            break;
            
        case KeyMapper::Action::MOVE_NW:
            y--;
            x--;
            break;
            
        default:
            break;
    }
    
    if (x != 0 || y != 0) {
        if (action_manager_->CanMove(x_ + x, y_ + y)) {
            x_ += x;
            y_ += y;
        }
    }
}

int Player::GetFovRadius() {
    assert(initialized_);

    return fov_radius_;
}
