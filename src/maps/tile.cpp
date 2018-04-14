#include "tile.hpp"

Tile::Tile(std::shared_ptr<libpmg::Tile> other) :
libpmg::Tile(other->GetX(), other->GetY(), other->GetTagList()) {
    this->is_path_explored_ = other->is_path_explored_;
    this->path_cost_ = other->path_cost_;
    
    explored_ = false;
}

void Tile::Draw(std::shared_ptr<TCODConsole> console, bool is_in_fov) {
    if (is_in_fov || explored_)
        console->setChar(GetX(), GetY(), GetChar());
}

void EmptyTile::Draw(std::shared_ptr<TCODConsole> console, bool is_in_fov) {
    if (is_in_fov)
        console->setCharForeground(GetX(), GetY(), kDefaultGroundInFovColor);
    else if (explored_)
        console->setCharForeground(GetX(), GetY(), kDefaultGroundExploredColor);
    
    Tile::Draw(console, is_in_fov);
}

void WallTile::Draw(std::shared_ptr<TCODConsole> console, bool is_in_fov) {
    if (is_in_fov)
        console->setCharForeground(GetX(), GetY(), kDefaultWallInFovColor);
    else if (explored_)
        console->setCharForeground(GetX(), GetY(), kDefaultWallExploredColor);
    
    Tile::Draw(console, is_in_fov);
}

void DoorTile::Draw(std::shared_ptr<TCODConsole> console, bool is_in_fov) {
    if (is_in_fov)
        console->setCharForeground(GetX(), GetY(), kDefaultWallInFovColor);
    else if (explored_)
        console->setCharForeground(GetX(), GetY(), kDefaultWallExploredColor);
    
    Tile::Draw(console, is_in_fov);
}
