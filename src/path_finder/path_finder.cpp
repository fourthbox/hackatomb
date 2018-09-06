#include "path_finder.hpp"

void PathFinder::Initialize(DungeonCategory const &category, std::size_t const &floor, MapsManager &maps_manager) {
    assert(!initialized_);
    
    maps_manager_ = &maps_manager;
    
    current_path_ = std::move(maps_manager_->AllocatePathFromFloor(category, floor, &path_callback_, 1.0f));
    
    initialized_ = true;
}

bool PathFinder::Walk(size_t &out_x, size_t &out_y, MapLocation const &from_location, MapLocation const &to_location, size_t steps) {
    assert(initialized_);
    assert(current_path_ != nullptr);
    
    // If the actor is taking 0 steps, return the starting posizion
    if (steps == 0) {
        out_x = from_location.x_;
        out_y = from_location.y_;
        return true;
    }
    
    // Converts steps to path index
    steps--;
    
    // If the steps are more than the path size, return destination
    if (steps != 0 && steps >= current_path_->size()) {
        out_x = to_location.x_;
        out_y = to_location.y_;
        return true;
    }
    
    int fx, fy, tx, ty, dx, dy;
    current_path_->getOrigin(&fx, &fy);
    current_path_->getDestination(&tx, &ty);
    
    // If either origin or destination changed, recalculate the path
    if (!RecomputeIfNeeded(from_location, to_location))
        return false;

    // Get the destination after the specified steps
    current_path_->get(steps, &dx, &dy);
    
    out_x = dx;
    out_y = dy;
    return true;
}

bool PathFinder::ExecuteCallbackAlongPath(MapLocation const &from_location, MapLocation const &to_location, std::function<void(Tile*)> callback) {
    assert(initialized_ && current_path_ != nullptr);
    
    // TODO: at the moment the path finder only support resolution on the same floor
    assert(from_location.dungeon_category_ == to_location.dungeon_category_
           && from_location.floor_ == to_location.floor_);
    
    // If either origin or destination changed, recalculate the path
    if (!RecomputeIfNeeded(from_location, to_location))
        return false;
    
    // Walk the path and execute the callback
    while (!current_path_->isEmpty()) {
        int x, y;
        
        if (!current_path_->walk(&x, &y, true))
            break;
        
        MapLocation new_location (from_location.dungeon_category_, from_location.floor_, x, y);
        
        auto tile {maps_manager_->GetTileFromFloor(new_location)};
        
        assert(tile);
        
        callback(tile);
    }
    
    return true;
}

bool PathFinder::ExecuteCallbackAlongLine(MapLocation const &from_location, MapLocation const &to_location, std::function<void(Tile*)> callback) {
    assert(initialized_);
    assert(from_location.dungeon_category_ == to_location.dungeon_category_);
    assert(from_location.floor_ == to_location.floor_);

    TCODLineCallback tcod_callback;
    tcod_callback.callback_ = callback;
    tcod_callback.maps_manager_ = maps_manager_;
    tcod_callback.category_ = from_location.dungeon_category_;
    tcod_callback.floor_ = from_location.floor_;
    
    return TCODLine::line(from_location.x_, from_location.y_, to_location.x_, to_location.y_, &tcod_callback);
}

bool PathFinder::ComputePath(MapLocation const &from_location, MapLocation const &to_location) {
    assert(initialized_);
    
    return current_path_->compute(from_location.x_, from_location.y_, to_location.x_, to_location.y_);
}

int PathFinder::GetPathLength(MapLocation const &from_location, MapLocation const &to_location) {
    assert(initialized_);
    
    // If either origin or destination changed, recalculate the path
    if (!RecomputeIfNeeded(from_location, to_location))
        return -1;

    return current_path_->size();
}

int PathFinder::GetLineLength(MapLocation const &from_location, MapLocation const &to_location) {
    assert(initialized_);
    
    TCODLine::init(from_location.x_, from_location.y_, to_location.x_, to_location.y_);
    
    int x, y, length {0};
    do {
        length++;
    } while (!TCODLine::step(&x, &y));

    return length;
}

bool PathFinder::RecomputeIfNeeded(MapLocation const &from_location, MapLocation const &to_location) {
    assert(initialized_);

    int fx, fy, tx, ty, dx, dy;
    current_path_->getOrigin(&fx, &fy);
    current_path_->getDestination(&tx, &ty);
    
    if (from_location.x_ != fx || from_location.y_ != fy ||
        to_location.x_ != tx || to_location.y_ != ty) {
        if (!ComputePath(from_location, to_location))
            return false;
    }
    
    return true;
}
