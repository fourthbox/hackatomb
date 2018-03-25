/**
 @file map.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef MAP_HPP_
#define MAP_HPP_

#include "libtcod.hpp"
#include "libpmg.hpp"

/**
 Class responsible for the management of a hackatomb dungeon Map.
 It extends functionalities both from an libpmg DungeonMap, and from a TCODMap.
 */
class Map : public libpmg::DungeonMap, public TCODMap {
public:
    /**
     Initializes the Map, starting from a libpmg::DungeonMap.
     @param map A pointer to the map which parameters will be copied into this instance.
     */
    Map(libpmg::DungeonMap &map);

    /**
     Draws the contents of the Map on a TCODConsole.
     @param console Pointer to the TCODConsole upon which to draw the contents of the Map.
     */
    void Draw(std::shared_ptr<TCODConsole> console);
    
    /**
     Checks wheter the specified coordinate is inside the field of view.
     If the debug flag CHEAT_NO_FOV_ is set, if will always return true.
     @param x The x coordinate.
     @param y The y coordinate.
     @return True if is in fov, false otherwise.
     */
    bool IsInFov(size_t x, size_t y, bool updateMapVisibility = false);
    
    /**
     Check if a tile is flagged as a wall.
     @param x X coordinate
     @param y Y coordinate
     @return True if the tile is a wall, false otherwise or if the tile fails the bounds check.
     */
    bool IsWall(size_t x, size_t y);
    
private:
    /**
     Bakes the libpmg map into the libtcod map.
     */
    void Dig();
    
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
    
    /**
     Get a wall character, based on the tiles adjacent to it.
     @param x X coordinate
     @param y Y coordinate
     @return The corresponding wall char
     */
    int GetWallChar(size_t x, size_t y);
    
};

//typedef std::shared_ptr<Map> Map_p;
typedef std::pair<size_t, size_t> Coordinate;
typedef std::shared_ptr<std::pair<size_t, size_t>> Coordinate_p;

#endif /* MAP_HPP_ */
