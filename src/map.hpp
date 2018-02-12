#ifndef MAP_HPP_
#define MAP_HPP_

#include "libpmg.hpp"
#include "libtcod.hpp"

class Map : public libpmg::DungeonMap, public TCODMap {
public:
    Map(std::shared_ptr<libpmg::DungeonMap> map);

    void Draw();
    bool IsInFov(size_t x, size_t y);
    
private:
    void Dig();
    
    // Getters and setters
    void SetExplored(size_t x, size_t y);
    bool IsExplored(size_t x, size_t y);
    
    /**
     Check if a tile is flagged as a wall.
     @param x X coordinate
     @param y Y coordinate
     @return True if the tile is a wall, false otherwise or if the tile fails the bounds check.
     */
    bool IsWall(size_t x, size_t y);

    /**
     Get a wall character, based on the tiles adjacent to it.
     @param x X coordinate
     @param y Y coordinate
     @return The corresponding wall char
     */
    int GetWallChar(size_t x, size_t y);
};

#endif /* MAP_HPP_ */
