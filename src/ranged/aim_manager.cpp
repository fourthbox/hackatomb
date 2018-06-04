#include "aim_manager.hpp"

#include "actor_manager.hpp"
#include "game_constants.hpp"

AimManager::AimManager() :
action_ {Action::NONE_},
action_manager_ {nullptr} {
    ResetCrosshair();
}

void AimManager::SetAction(Action action) {
    assert(initialized_);
    
    action_ = action;
}

void AimManager::Initialize(ActionManager &action_manager, ActorManager &actor_manager, MapsManager &maps_manager) {
    assert(!action_manager_ && !initialized_);
    
    action_manager_ = &action_manager;
    actor_manager_ = &actor_manager;
    
    path_finder_.Initialize(maps_manager);
    
    initialized_ = true;
}

void AimManager::Update() {
    assert(initialized_
           && crosshair_x_ != std::experimental::nullopt
           && crosshair_y_ != std::experimental::nullopt
           && range_ != std::experimental::nullopt
           && action_manager_->GetTurnPhase() == TurnPhase::AIM_
           && mode_ != CrosshairMode::NONE_);
    
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
    
    // Move the crosshair position
    if (x != 0 || y != 0) {
        auto new_x {*crosshair_x_ + x}, new_y {*crosshair_y_ + y};
        
        // Check if it's going out of range
        auto length {path_finder_.GetLineLength(actor_manager_->GetPlayer().GetPosition().first,
                                                actor_manager_->GetPlayer().GetPosition().second,
                                                new_x,
                                                new_y)};

        // Note:If length is -1, the pathfinder found an obstacle
        // If out of range, exit the function
        if (length > 5)
            return;

        if (action_manager_->CanMove(new_x, new_y)) {
            crosshair_x_ = std::experimental::make_optional(new_x);
            crosshair_y_ = std::experimental::make_optional(new_y);
        }
    }
}

void AimManager::Draw(TCODConsole &console) {
    assert(initialized_
           && crosshair_x_ != std::experimental::nullopt
           && crosshair_y_ != std::experimental::nullopt
           && range_ != std::experimental::nullopt
           && action_manager_->GetTurnPhase() == TurnPhase::AIM_
           && mode_ != CrosshairMode::NONE_);
    
    // Drawing the crosshair
    console.setChar(crosshair_x_.value_or(actor_manager_->GetPlayer().GetPosition().first),
                    crosshair_y_.value_or(actor_manager_->GetPlayer().GetPosition().second),
                    kCharCrosshair);

    console.setCharForeground(crosshair_x_.value_or(actor_manager_->GetPlayer().GetPosition().first),
                              crosshair_y_.value_or(actor_manager_->GetPlayer().GetPosition().second),
                              kCrosshairColor);
        
    // Drawing the trail
    if (crosshair_x_ != std::experimental::nullopt && crosshair_y_ != std::experimental::nullopt) {
        auto success { path_finder_.ExecuteCallbackAlongLine(actor_manager_->GetPlayer().GetPosition().first,
                                                             actor_manager_->GetPlayer().GetPosition().second,
                                                             *crosshair_x_,
                                                             *crosshair_y_,
                                                             [] (Tile *tile) { tile->ToggleHighlight(true); }
                                                             )};
    }
}

void AimManager::ResetCrosshair() {
    crosshair_x_ = std::experimental::nullopt;
    crosshair_y_ = std::experimental::nullopt;
    range_ = std::experimental::nullopt;
    mode_ = CrosshairMode::NONE_;
}

void AimManager::SetupCrossshair(CrosshairMode mode, int range) {
    assert(initialized_
           && crosshair_x_ == std::experimental::nullopt
           && crosshair_y_ == std::experimental::nullopt
           && range_ == std::experimental::nullopt
           && mode_ == CrosshairMode::NONE_
           && mode != CrosshairMode::NONE_
           && action_manager_->GetTurnPhase() == TurnPhase::AIM_);
    
    mode_ = mode;
    range_ = std::experimental::make_optional(range);
    
    // Put the crosshair on the player position
    crosshair_x_ = std::experimental::make_optional(actor_manager_->GetPlayer().GetPosition().first);
    crosshair_y_ = std::experimental::make_optional(actor_manager_->GetPlayer().GetPosition().second);
}
