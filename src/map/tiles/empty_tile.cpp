#include "empty_tile.hpp"

void EmptyTile::Draw(TCODConsole &console, bool is_in_fov) {
    if (is_in_fov || explored_) {
        console.setCharBackground(GetX(), GetY(), kDefaultGroundColor);
        console.setCharForeground(GetX(), GetY(), kDefaultWallColor);
    }
    
    Tile::Draw(console, is_in_fov);
}
