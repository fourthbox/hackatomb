#ifndef DOOR_TILE_HPP_
#define DOOR_TILE_HPP_

#include "game_constants.hpp"
#include "tile.hpp"

class DoorTile : public Tile {
public:
    DoorTile(libpmg::Tile *other) : Tile (other) {
        is_open_ = false;
        is_locked_ = false;
        type_ = TileType::DOOR_;
    }
    void Draw(TCODConsole &console, bool is_in_fov) override;
    
    inline int GetChar() override { return (is_open_ ? kCharOpenDoor : kCharClosedDoor ); }
    bool IsTransparent() override { return is_open_; }
    bool IsWalkable() override { return is_open_; }
    
    inline bool IsOpen() { return is_open_; }
    inline void Open() { is_open_ = true; }
    inline void Close() { is_open_ = false; }
    
    inline bool IsLocked() { return is_locked_; }
    inline void Unlock() { is_locked_ = false; }
    
private:
    bool is_open_, is_locked_;
};

#endif /* DOOR_TILE_HPP_ */
