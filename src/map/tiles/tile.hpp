#ifndef TILE_HPP_
#define TILE_HPP_

#include "libpmg.hpp"
#include "libtcod.hpp"

enum struct TileType {
    FLOOR_,
    WALL_,
    DOOR_
};

class Tile : public libpmg::Tile {
public:
    Tile(libpmg::Tile *other);
    
    virtual void Draw(TCODConsole *console, bool is_in_fov);
    virtual bool IsTransparent() = 0;
    virtual bool IsWalkable() = 0;
    virtual int GetChar() = 0;
    
    inline bool IsExplored() { return explored_; }
    inline void Explore() { explored_ = true; }
    
    inline TileType GetType() { return type_; }
    
protected:
    bool explored_;
    TileType type_;
};

#endif /* TILE_HPP_ */
