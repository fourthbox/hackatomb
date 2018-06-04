#include "path_finder.hpp"

void PathFinder::Initialize(MapsManager &maps_manager) {
    assert(!initialized_);
    
    path_callback_ = std::make_unique<TCODPathCallback>();
    
    maps_manager_ = &maps_manager;
    
    current_path_ = std::move(maps_manager_->AllocatePathFromCurrentFloor(path_callback_.get(), 1.0f));
    
    initialized_ = true;
}

bool PathFinder::Walk(size_t &out_x, size_t &out_y, size_t from_x, size_t from_y, size_t to_x, size_t to_y, size_t steps) {
    assert(initialized_ && current_path_ != nullptr);
    
    // If the actor is taking 0 steps, return the starting posizion
    if (steps == 0) {
        out_x = from_x;
        out_y = from_y;
        return true;
    }
    
    // Converts steps to path index
    steps--;
    
    // If the steps are more than the path size, return destination
    if (steps != 0 && steps >= current_path_->size()) {
        out_x = to_x;
        out_y = to_y;
        return true;
    }
    
    // If either origin or destination changed, recalculate the path
    int fx, fy, tx, ty, dx, dy;
    current_path_->getOrigin(&fx, &fy);
    current_path_->getDestination(&tx, &ty);

    if (from_x != fx || from_y != fy ||
        to_x != tx || to_y != ty) {
        if (!ComputePath(from_x, from_y, to_x, to_y))
            return false;
    }
    
    // Get the destination after the specified steps
    current_path_->get(steps, &dx, &dy);
    
    out_x = dx;
    out_y = dy;
    return true;
}

bool PathFinder::ExecuteCallbackAlongPath(size_t from_x, size_t from_y, size_t to_x, size_t to_y, std::function<void(Tile*)> callback)
{
    assert(initialized_ && current_path_ != nullptr);
    
    // If either origin or destination changed, recalculate the path
    int fx, fy, tx, ty, dx, dy;
    current_path_->getOrigin(&fx, &fy);
    current_path_->getDestination(&tx, &ty);
    
    if (from_x != fx || from_y != fy ||
        to_x != tx || to_y != ty) {
        if (!ComputePath(from_x, from_y, to_x, to_y))
            return false;
    }
    
    // Walk the path and execute the callback
    while (!current_path_->isEmpty()) {
        int x, y;
        if (current_path_->walk(&x, &y, true)) {
            auto tile {maps_manager_->GetTileFromFloor(x, y)};
            
            assert(tile);
            
            callback(tile);
        }
        else {
            break;
        }
    }
    
    return true;
}

bool PathFinder::ComputePath(size_t from_x, size_t from_y, size_t to_x, size_t to_y) {
    assert(initialized_);
    
    return current_path_->compute(from_x, from_y, to_x, to_y);
}
