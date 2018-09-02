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
    TCODLineCallback() :
    maps_manager_ {nullptr},
    floor_ {std::experimental::nullopt},
    category_ {std::experimental::nullopt} {
    }
    
    std::function<void(Tile*)> callback_;
    MapsManager *maps_manager_;
    std::experimental::optional<std::size_t> floor_;
    std::experimental::optional<DungeonCategory> category_;
    
    bool putPoint (int x, int y) override {
        assert (callback_);
        assert (maps_manager_);
        assert (floor_);
        assert (category_);
        
        MapLocation location (*category_, *floor_, x, y);
        
        auto tile {maps_manager_->GetTileFromFloor(location)};
        
        assert (tile);
        
        callback_(tile);
        
        return true;
    }
};

class PathFinder : public InitiableObject {
public:
    void Initialize(DungeonCategory const &category, std::size_t const &floor, MapsManager &maps_manager);
    
    /**
     Move an actor by changing the positions for a specified amount of steps.
     Only recompute the path if the starting or end potision changed
     @param out_x Output X coordinate.
     @param out_y Output Y coordinate.
     @param from_location Starting map coordinate.
     @param to_location Ending map coordinate.
     @param steps Number of steps. Default: 1
     @return True if succesfully moved, false otherwise.
     */
    bool Walk(size_t &out_x, size_t &out_y, MapLocation const &from_location, MapLocation const &to_location, size_t steps = 1);
    
    bool ExecuteCallbackAlongPath(MapLocation const &from_location, MapLocation const &to_location,
                                  std::function<void(Tile*)> callback);
    bool ExecuteCallbackAlongLine(MapLocation const &from_location, MapLocation const &to_location,
                                  std::function<void(Tile*)> callback);
    
    int GetPathLength(MapLocation const &from_location, MapLocation const &to_location);
    int GetLineLength(MapLocation const &from_location, MapLocation const &to_location);
    
private:
    TCODPathCallback path_callback_;
    std::unique_ptr<TCODPath> current_path_;
    MapsManager *maps_manager_;

    bool ComputePath(MapLocation const &from_location, MapLocation const &to_location);
    bool RecomputeIfNeeded(MapLocation const &from_location, MapLocation const &to_location);
};

#endif /* PATH_FINDER_HPP_ */
