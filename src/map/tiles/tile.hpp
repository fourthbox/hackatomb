#ifndef TILE_HPP_
#define TILE_HPP_

#include "libpmg.hpp"
#include "libtcod.hpp"

enum struct TileType {
    FLOOR_,
    WALL_,
    DOOR_,
    STAIRS_
};

class Tile : public libpmg::Tile {
public:
    Tile(libpmg::Tile *other);
    
    virtual void Draw(TCODConsole &console, bool is_in_fov);
    virtual bool IsTransparent() = 0;
    virtual bool IsWalkable() = 0;
    virtual int GetChar() = 0;
    
    inline bool IsExplored() { return is_explored_; }
    inline void Explore() { is_explored_ = true; }
    
    inline TileType GetType() { return type_; }
    
    inline void ToggleHighlight(bool toggle) { is_highlighted_ = toggle; }
    
protected:
    bool is_explored_, is_highlighted_;
    TileType type_;
};

#endif /* TILE_HPP_ */
