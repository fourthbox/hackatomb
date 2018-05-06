#include "door_tile.hpp"

void DoorTile::Draw(TCODConsole *console, bool is_in_fov) {
    if (is_in_fov || explored_) {
        console->setCharBackground(GetX(), GetY(), kDefaultGroundColor);
        console->setCharForeground(GetX(), GetY(), kDefaultDoorColor);
    }
    
    Tile::Draw(console, is_in_fov);
}
