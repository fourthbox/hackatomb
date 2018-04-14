#ifndef WALL_TILE_HPP_
#define WALL_TILE_HPP_

#include "initiable_object.hpp"
#include "tile.hpp"

class Map;

class WallTile : public Tile, public InitiableObject {
public:
    WallTile(std::shared_ptr<libpmg::Tile> other) : Tile(other) { type_ = TileType::WALL_; }
    void Initialize(Map *map);
    
    void Draw(std::shared_ptr<TCODConsole> console, bool is_in_fov) override;
    
    int GetChar() override;
    
private:
    Map *map_;
};

#endif /* WALL_TILE_HPP_ */
