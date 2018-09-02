#include "aim_manager.hpp"

#include "game_constants.hpp"

AimManager::AimManager() :
action_ {Action::NONE_} {
    ResetCrosshair();
}

void AimManager::SetAction(Action action) {
    assert(initialized_);
    
    action_ = action;
}

void AimManager::Initialize(DungeonCategory const &category, std::size_t const &floor, MapsManager &maps_manager) {
    assert(!initialized_);
    
    path_finder_.Initialize(category, floor, maps_manager);
    
    initialized_ = true;
}

void AimManager::Update(Player const &player, ActionManager &action_manager, MapsManager &maps_manager) {
    assert(initialized_);
    assert(crosshair_location_);
    assert(range_);
    assert(mode_ != CrosshairMode::NONE_);
    
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
        // Pick crosshair location on map
        MapLocation new_location (player.GetMapLocation().dungeon_category_,
                                  player.GetMapLocation().floor_,
                                  crosshair_location_->x_ + x,
                                  crosshair_location_->y_ + y);

        if (maps_manager.IsInFov(player, new_location) && action_manager.CanMove(new_location)) {
            
            // Check if it's going out of range
            auto length {path_finder_.GetLineLength(player.GetMapLocation(), new_location)};
            
            // Note: If length is -1, the pathfinder found an obstacle
            // If out of range, exit the function
            if (length <= range_)
                crosshair_location_ = std::experimental::make_optional(new_location);
        }
    }
}

void AimManager::DrawTrail(TCODConsole &console, MapLocation const &player_location) {
    assert(initialized_ && crosshair_location_ && range_ && mode_ != CrosshairMode::NONE_);
    
    // Highlight tile callback
    auto callback = [=] (Tile *tile) {
        if (tile->GetXY() != player_location.GetPosition()
            && tile->GetXY() != std::make_pair(crosshair_location_->x_, crosshair_location_->y_))
            tile->ToggleHighlight(true);
    };

    // Draw the trail
    auto success { path_finder_.ExecuteCallbackAlongLine(player_location, *crosshair_location_, callback) };
}

void AimManager::DrawCrosshair(TCODConsole &console, MapLocation const &player_location) {
    assert(initialized_ && crosshair_location_ && range_ && mode_ != CrosshairMode::NONE_);
    
    // Draw crosshair callback
    auto callback = [=, &console] (Tile *tile) {
        if (tile->GetXY() == std::make_pair(crosshair_location_->x_, crosshair_location_->y_)) {
            console.setChar(crosshair_location_->x_, crosshair_location_->y_, kCharCrosshair);
            console.setCharForeground(crosshair_location_->x_, crosshair_location_->y_, kCrosshairColor);
        }
    };
    
    // Draw the crosshair
    auto success { path_finder_.ExecuteCallbackAlongLine(player_location, *crosshair_location_, callback) };
}

void AimManager::ResetCrosshair() {
    crosshair_location_ = std::experimental::nullopt;
    range_ = std::experimental::nullopt;
    mode_ = CrosshairMode::NONE_;
    
    action_ = Action::NONE_;
}

void AimManager::SetupCrossshair(CrosshairMode mode, int range, Player &player, std::vector<Actor*> actor_list, MapsManager &maps_manager) {
    assert(initialized_);
    assert(mode != CrosshairMode::NONE_);
    
    mode_ = mode;
    range_ = std::experimental::make_optional(range);
    
    // Put the crosshair on the closest enemy in range
    if (auto monster {player.GetClosestActorInRange(actor_list, range, maps_manager)}; monster)
        crosshair_location_ = std::experimental::make_optional(monster->GetMapLocation());
    else
        // Otherwise put it on the player
        crosshair_location_ = std::experimental::make_optional(player.GetMapLocation());
}

MapLocation const &AimManager::GetCrosshairLocation() const {
    assert(initialized_ && crosshair_location_ && range_);

    return *crosshair_location_;
}
