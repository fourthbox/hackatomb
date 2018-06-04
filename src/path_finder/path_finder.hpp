#ifndef PATH_FINDER_HPP_
#define PATH_FINDER_HPP_

#include "game_globals.hpp"
#include "initiable_object.hpp"
#include "libtcod.hpp"
#include "maps_manager.hpp"

class TCODPathCallback : public ITCODPathCallback {
    public :
    float getWalkCost(int from_x, int from_y, int to_x, int to_y, void *user_data ) const override {
        assert(user_data != nullptr);
        auto map {static_cast<Map*> (user_data)};
        
        return map->IsWall(to_x, to_y) ? 0.0f : 1.0f;
    }
};

class TCODLineCallback : public TCODLineListener {
public:
    TCODLineCallback() : maps_manager_ {nullptr} {}
    
    std::function<void(Tile*)> callback_;
    MapsManager *maps_manager_;
    
    bool putPoint (int x, int y) override {
        assert (callback_ && maps_manager_);
        
        auto tile {maps_manager_->GetTileFromFloor(x, y)};
        
        assert (tile);
        
        callback_(tile);
        
        return true;
    }
};

class PathFinder : public InitiableObject {
public:
    void Initialize(MapsManager &maps_manager);
    
    /**
     Move an actor by changing the positions for a specified amount of steps.
     Only recompute the path if the starting or end potision changed
     @param out_x Output X coordinate.
     @param out_y Output Y coordinate.
     @param from_x Starting X coordinate.
     @param from_y Starting Y coordinate.
     @param to_x Ending X coordinate.
     @param to_y Ending Y coordinate.
     @param steps Number of steps. Default: 1
     @return True if succesfully moved, false otherwise.
     */
    bool Walk(size_t &out_x, size_t &out_y, size_t from_x, size_t from_y, size_t to_x, size_t to_y, size_t steps = 1);
    
    bool ExecuteCallbackAlongPath(size_t from_x, size_t from_y, size_t to_x, size_t to_y,
                                  std::function<void(Tile*)> callback);
    bool ExecuteCallbackAlongLine(size_t from_x, size_t from_y, size_t to_x, size_t to_y,
                                  std::function<void(Tile*)> callback);
    
    int GetPathLength(size_t from_x, size_t from_y, size_t to_x, size_t to_y);
    int GetLineLength(size_t from_x, size_t from_y, size_t to_x, size_t to_y);
    
private:
    TCODPathCallback path_callback_;
    std::unique_ptr<TCODPath> current_path_;
    MapsManager *maps_manager_;

    bool ComputePath(size_t from_x, size_t from_y, size_t to_x, size_t to_y);
    bool RecomputeIfNeeded(size_t from_x, size_t from_y, size_t to_x, size_t to_y);
};

#endif /* PATH_FINDER_HPP_ */
