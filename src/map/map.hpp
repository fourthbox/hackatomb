/**
 @file map.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef MAP_HPP_
#define MAP_HPP_

#include <experimental/optional>

#include "dungeon_factory.hpp"
#include "libtcod.hpp"
#include "libpmg.hpp"
#include "tile.hpp"

/**
 Class responsible for the management of a hackatomb dungeon Map.
 It extends functionalities both from an libpmg DungeonMap, and from a TCODMap.
 */
class Map : public TCODMap {
    friend class MapsManager;
    
public:
    /**
     Initializes the Map, starting from a libpmg::DungeonMap.
     Deallocates the original vector of Tiles inside DungeonMap, and then fills map_.
     @param map A pointer to the map which parameters will be copied into this instance.
     */
    Map(libpmg::DungeonMap &map);
    
    /**
     Check if a tile is flagged as a wall.
     @param x X coordinate
     @param y Y coordinate
     @return True if the tile is a wall, false otherwise or if the tile fails the bounds check.
     */
    bool IsWall(size_t x, size_t y);

    bool HasDoor(size_t x, size_t y);
    
    inline std::vector<std::unique_ptr<libpmg::Room>> &GetRoomList() { return room_list_; }
    
    inline Tile *GetEntranceTile() { return entrance_stair_; }
    inline Tile *GetExitTile() { return exit_stair_; }
    
    inline void SetDungeonCategory(DungeonCategory category) { dungeon_category_ = category; }
    
private:
    std::vector<std::unique_ptr<Tile>> map_;
    std::vector<std::unique_ptr<libpmg::Room>> room_list_;
    std::unique_ptr<libpmg::MapConfigs> map_configs_;
    Tile *entrance_stair_, *exit_stair_;
    DungeonCategory dungeon_category_;
    
    std::size_t experience_yield_; /**< The amount of experience that can be yield from this dungeon */
    
    /**
     Draws the contents of the Map on a TCODConsole.
     @param console Pointer to the TCODConsole upon which to draw the contents of the Map.
     */
    void Draw(TCODConsole &console);
    
    /**
     Checks wheter the specified coordinate is inside the field of view.
     @param x The x coordinate.
     @param y The y coordinate.
     @return True if is in fov, false otherwise.
     */
    bool IsInFov(size_t x, size_t y);
    
    /**
     Bakes the libpmg map into the libtcod map.
     */
    void DigTcodMap();
    
    void DigPmgMap(libpmg::DungeonMap &map);
    
    // Getters and setters
    /**
     Set a tile as explored.
     @param x The X coordinate.
     @param y The Y coordinate.
     */
    void SetExplored(size_t x, size_t y);
    
    /**
     Check whether a tile is explored.
     @param x The X coordinate.
     @param y The Y coordinate.
     @return True if the tile has been explored, false otherwise.
     */
    bool IsExplored(size_t x, size_t y);
        
    void UpdateTcodProperties(size_t x, size_t y);
    void UpdateTcodProperties(Tile *tile);
    
    Tile *GetTile(size_t x, size_t y);
    
    bool BoundsCheck(std::size_t x, std::size_t y);
    
    void SetAllExplored();
};

typedef std::pair<size_t, size_t> Coordinate;
typedef std::experimental::optional<Coordinate> CoordinateOpt_n;


#endif /* MAP_HPP_ */
