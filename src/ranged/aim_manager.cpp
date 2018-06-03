#include "aim_manager.hpp"

#include "actor_manager.hpp"
#include "game_constants.hpp"

AimManager::AimManager() :
action_ {Action::NONE_},
action_manager_ {nullptr} {
    ResetCrosshair();
}

void AimManager::Initialize(ActionManager &action_manager, ActorManager &actor_manager) {
    assert(!action_manager_ && !initialized_);
    
    action_manager_ = &action_manager;
    actor_manager_ = &actor_manager;
    
    initialized_ = true;
}

void AimManager::Update() {
    assert(initialized_);
    
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
        default:
            return;
    }
    
    // If the crosshair was reset, set it to the player position
    if (crosshair_x_ == std::experimental::nullopt && crosshair_y_ == std::experimental::nullopt) {
        crosshair_x_ = std::experimental::make_optional(actor_manager_->GetPlayer().GetPosition().first);
        crosshair_y_ = std::experimental::make_optional(actor_manager_->GetPlayer().GetPosition().second);
    }
    
    // Move the crosshair position
    if (x != 0 || y != 0) {
        if (action_manager_->CanMove(*crosshair_x_ + x, *crosshair_y_ + y)) {
            crosshair_x_ = std::experimental::make_optional(*crosshair_x_ + x);
            crosshair_y_ = std::experimental::make_optional(*crosshair_y_ + y);
        }
    }
}

void AimManager::Draw(TCODConsole &console) {
    assert(initialized_);
    
    console.setChar(crosshair_x_.value_or(actor_manager_->GetPlayer().GetPosition().first),
                    crosshair_y_.value_or(actor_manager_->GetPlayer().GetPosition().second),
                    kCharCrossHair);

    console.setCharForeground(crosshair_x_.value_or(actor_manager_->GetPlayer().GetPosition().first),
                              crosshair_y_.value_or(actor_manager_->GetPlayer().GetPosition().second),
                              kCrossHairColor);
}

void AimManager::ResetCrosshair() {
    crosshair_x_ = std::experimental::nullopt;
    crosshair_y_ = std::experimental::nullopt;
}
