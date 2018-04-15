#ifndef EMPTY_TILE_HPP_
#define EMPTY_TILE_HPP_

#include "tile.hpp"

#include "game_constants.hpp"

class EmptyTile : public Tile {
public:
    EmptyTile(std::shared_ptr<libpmg::Tile> other) : Tile(other) { type_ = TileType::FLOOR_; }
    void Draw(std::shared_ptr<TCODConsole> console, bool is_in_fov) override;
    
    inline int GetChar() override { return kCharFloor; }
    inline bool IsTransparent() override { return true; }
    inline bool IsWalkable() override { return true; }
};

#endif /* EMPTY_TILE_HPP_ */
