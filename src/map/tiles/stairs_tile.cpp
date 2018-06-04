#include "stairs_tile.hpp"

void StairsTile::Draw(TCODConsole &console, bool is_in_fov) {
    if (is_in_fov || is_explored_) {
        console.setCharBackground(GetX(), GetY(), kDefaultGroundColor);
        console.setCharForeground(GetX(), GetY(), kDefaultStairsColor);
    }
    
    Tile::Draw(console, is_in_fov);
}
