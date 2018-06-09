#include "aim_manager.hpp"

#include "actor_manager.hpp"
#include "game_constants.hpp"

AimManager::AimManager() :
action_ {Action::NONE_} {
    ResetCrosshair();
}

void AimManager::SetAction(Action action) {
    assert(initialized_);
    
    action_ = action;
}

void AimManager::Initialize(MapsManager &maps_manager) {
    assert(!initialized_);
    
    path_finder_.Initialize(maps_manager);
    
    initialized_ = true;
}

void AimManager::Update(ActionManager &action_manager, ActorManager &actor_manager, MapsManager &maps_manager) {
    assert(initialized_
           && crosshair_x_ != std::experimental::nullopt
           && crosshair_y_ != std::experimental::nullopt
           && range_ != std::experimental::nullopt
           && action_manager.GetTurnPhase() == TurnPhase::AIM_
           && mode_ != CrosshairMode::NONE_);
    
    auto player_position {actor_manager.GetPlayer().GetPosition()};
    
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
        
        if (actor_manager.GetPlayer().CanSee(new_x, new_y, maps_manager)
            && action_manager.CanMove(new_x, new_y)) {
            
            // Check if it's going out of range
            auto length {path_finder_.GetLineLength(player_position.first,
                                                    player_position.second,
                                                    new_x,
                                                    new_y)};
            
            // Note: If length is -1, the pathfinder found an obstacle
            // If out of range, exit the function
            if (length <= range_) {
                crosshair_x_ = std::experimental::make_optional(new_x);
                crosshair_y_ = std::experimental::make_optional(new_y);
            }
        }
    }
}

void AimManager::DrawTrail(TCODConsole &console, ActorManager &actor_manager) {
    assert(initialized_
           && crosshair_x_ != std::experimental::nullopt
           && crosshair_y_ != std::experimental::nullopt
           && range_ != std::experimental::nullopt
           && mode_ != CrosshairMode::NONE_);
    
    auto player_position {actor_manager.GetPlayer().GetPosition()};
    
    auto x {crosshair_x_.value_or(player_position.first)};
    auto y {crosshair_y_.value_or(player_position.second)};
    
    // Highlight tile callback
    auto callback = [&] (Tile *tile) {
        if (tile->GetXY() != player_position
            && tile->GetXY() != std::make_pair(x, y))
            tile->ToggleHighlight(true);
    };

    // Draw the trail
    if (crosshair_x_ != std::experimental::nullopt && crosshair_y_ != std::experimental::nullopt) {
        auto success { path_finder_.ExecuteCallbackAlongLine(player_position.first,
                                                             player_position.second,
                                                             *crosshair_x_,
                                                             *crosshair_y_,
                                                             callback
                                                             )};
    }
}

void AimManager::DrawCrosshair(TCODConsole &console, ActorManager &actor_manager) {
    assert(initialized_
           && crosshair_x_ != std::experimental::nullopt
           && crosshair_y_ != std::experimental::nullopt
           && range_ != std::experimental::nullopt
           && mode_ != CrosshairMode::NONE_);
    
    auto player_position {actor_manager.GetPlayer().GetPosition()};
    
    auto x {crosshair_x_.value_or(player_position.first)};
    auto y {crosshair_y_.value_or(player_position.second)};
    
    // Draw crosshair callback
    auto callback = [&] (Tile *tile) {
        if (tile->GetXY() == std::make_pair(x, y)) {
            console.setChar(x, y, kCharCrosshair);
            console.setCharForeground(x, y, kCrosshairColor);
        }
    };
    
    // Draw the crosshair
    if (crosshair_x_ != std::experimental::nullopt && crosshair_y_ != std::experimental::nullopt) {
        auto success { path_finder_.ExecuteCallbackAlongLine(player_position.first,
                                                             player_position.second,
                                                             *crosshair_x_,
                                                             *crosshair_y_,
                                                             callback
                                                             )};
    }
}

void AimManager::ResetCrosshair() {
    crosshair_x_ = std::experimental::nullopt;
    crosshair_y_ = std::experimental::nullopt;
    range_ = std::experimental::nullopt;
    mode_ = CrosshairMode::NONE_;
}

void AimManager::SetupCrossshair(CrosshairMode mode, int range, ActorManager &actor_manager, MapsManager &maps_manager) {
    assert(initialized_
           && crosshair_x_ == std::experimental::nullopt
           && crosshair_y_ == std::experimental::nullopt
           && range_ == std::experimental::nullopt
           && mode_ == CrosshairMode::NONE_
           && mode != CrosshairMode::NONE_);
    
    auto player_position {actor_manager.GetPlayer().GetPosition()};

    mode_ = mode;
    range_ = std::experimental::make_optional(range);
    
    // Put the crosshair on the closest enemy in range
    if (auto monster {actor_manager.GetPlayer().GetClosestActorInFov(actor_manager, maps_manager)}; monster != nullptr) {
        crosshair_x_ = std::experimental::make_optional(monster->GetPosition().first);
        crosshair_y_ = std::experimental::make_optional(monster->GetPosition().second);
    } else {
        // Otherwise put it on the player
        crosshair_x_ = std::experimental::make_optional(player_position.first);
        crosshair_y_ = std::experimental::make_optional(player_position.second);
    }
    
}

void AimManager::PerformActionOnCrosshair(ActionManager &action_manager, ActorManager &actor_manager) {
    assert(initialized_
           && crosshair_x_ != std::experimental::nullopt
           && crosshair_y_ != std::experimental::nullopt
           && range_ != std::experimental::nullopt
           && mode_ != CrosshairMode::NONE_
           && action_manager.GetTurnPhase() == TurnPhase::AIM_);

    action_manager.ShootAction(actor_manager.GetPlayer(), *crosshair_x_, *crosshair_y_);
}
