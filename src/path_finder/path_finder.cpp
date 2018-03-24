#include "path_finder.hpp"

#include "game_globals.hpp"

class TCODPathCallback : public ITCODPathCallback {
    public :
    float getWalkCost(int from_x, int from_y, int to_x, int to_y, void *user_data ) const override {
        assert(user_data != nullptr);
        auto map {static_cast<Map*> (user_data)};

        if (map->IsWall(to_x, to_y))
            return 0.0f;
        
        return 1.0f;
    }
};

PathFinder::PathFinder() {
    assert(!initialized_);

    current_path_ = nullptr;
}

void PathFinder::Initialize(Map_p map) {
    assert(!initialized_);
    initialized_ = true;
    
    SetMap(map);
}

Coordinate_p PathFinder::Walk(size_t from_x, size_t from_y, size_t to_x, size_t to_y, size_t steps) {
    assert(initialized_);
    
    if (current_path_ == nullptr) {
        if (!ComputePath(from_x, from_y, to_x, to_y))
            return nullptr;
    }
    
//    // If the steps are more than the path size, return destination
//    if (steps >= current_path_->size())
//        return std::make_shared<std::pair<size_t, size_t>> (std::make_pair(to_x, to_y));
    
    // If either origin or destination changed, recalculate the path
    int fx, fy, tx, ty, dx, dy;
    current_path_->getOrigin(&fx, &fy);
    current_path_->getDestination(&tx, &ty);

    if (from_x != fx || from_y != fy ||
        to_x != tx || to_y != ty) {
        if (!ComputePath(from_x, from_y, to_x, to_y))
            return nullptr;
    }
    
    // Get the destination after the specified steps
    current_path_->get(steps, &dx, &dy);
    
    return std::make_shared<std::pair<size_t, size_t>> (std::make_pair(dx, dy));
}

bool PathFinder::ComputePath(size_t from_x, size_t from_y, size_t to_x, size_t to_y) {
    assert(initialized_);
    
    return current_path_->compute(from_x, from_y, to_x, to_y);
}

void PathFinder::SetMap(Map_p map) {
    assert(initialized_);
    
    current_path_ = std::make_shared<TCODPath>(map->getWidth(), map->getHeight(), new TCODPathCallback, map.get(), 1.0f);
}
