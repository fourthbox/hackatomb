#ifndef STAIRS_TILE_HPP_
#define STAIRS_TILE_HPP_

#include "game_constants.hpp"
#include "tile.hpp"

class StairsTile : public Tile {
public:
    StairsTile(libpmg::Tile *other, bool is_upstairs) : Tile (other) {
        type_ = TileType::STAIRS_;
        is_upstairs_ = is_upstairs;
    }
    
    void Draw(TCODConsole &console, bool is_in_fov) override;
    
    inline int GetChar() override { return (is_upstairs_ ? kCharUpstairs : kCharDownstairs ); }
    bool IsTransparent() override { return true; }
    bool IsWalkable() override { return true; }

    inline bool IsUpstairs() { return is_upstairs_; }
    
    inline void Enter() { /* enter new map */ }
    
private:
    bool is_upstairs_;
};

#endif /* STAIRS_TILE_HPP_ */
