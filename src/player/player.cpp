#include "player.hpp"

#include "game_constants.hpp"

Player::Player() {
    assert(!initialized_);
    
    action_ = Action::NONE_;
}

bool Player::Update(size_t speed, ActionManager &action_manager, MapsManager &maps_manager) {
    assert(initialized_);
    
    if (!Actor::Update(speed, action_manager, maps_manager))
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
            action_manager.ActorWaited();
            return false;
            
        default:
            return false;
    }
    
    if (x != 0 || y != 0) {
        MapLocation location (map_location_->dungeon_category_,
                              map_location_->floor_,
                              map_location_->x_ + x,
                              map_location_->y_ + y);
        
        if (action_manager.CanMove(location)
            && !action_manager.CanAtttack(location)) {
            MoveToLocation(location);
            action_manager.ActorMoved();
        } else {
            if (action_manager.PerformAction(*this, location))
                action_manager.ActorMoved();
        }
    }
    
    return true;
}

void Player::SetAction(Action action) {
    assert(initialized_);

    action_ = action;
}
