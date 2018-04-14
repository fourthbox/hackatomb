#ifndef TILE_HPP_
#define TILE_HPP_

#include "game_constants.hpp"
#include "libpmg.hpp"

enum struct TileType {
    FLOOR_,
    WALL_,
    DOOR_
};

class Tile : public libpmg::Tile {
public:
    Tile(std::shared_ptr<libpmg::Tile> other);
    
    virtual void Draw(std::shared_ptr<TCODConsole> console, bool is_in_fov);
    virtual int GetChar() = 0;
    
    inline bool IsExplored() { return explored_; }
    inline void Explore() { explored_ = true; }
    
    inline TileType GetType() { return type_; }
    
protected:
    bool explored_;
    TileType type_;
};

class EmptyTile : public Tile {
public:
    EmptyTile(std::shared_ptr<libpmg::Tile> other) : Tile(other) { type_ = TileType::FLOOR_; }
    void Draw(std::shared_ptr<TCODConsole> console, bool is_in_fov) override;

    inline int GetChar() override { return kCharFloor; }
};

class WallTile : public Tile {
public:
    WallTile(std::shared_ptr<libpmg::Tile> other) : Tile(other) { type_ = TileType::WALL_; }
    void Draw(std::shared_ptr<TCODConsole> console, bool is_in_fov) override;

    inline int GetChar() override { return wall_char_; }
    // temp
    int wall_char_;             /**< Absolutely TEMPORARY variable. will deen to implement the logic in GetChar() */
};

class DoorTile : public Tile {
public:
    DoorTile(std::shared_ptr<libpmg::Tile> other) : Tile (other) {
        is_open_ = false;
        is_locked_ = false;
        type_ = TileType::WALL_;
    }
    void Draw(std::shared_ptr<TCODConsole> console, bool is_in_fov) override;
    
    inline int GetChar() override { return (is_open_ ? kCharOpenDoor : kCharClosedDoor ); }
    
    inline bool IsOpen() { return is_open_; }
    inline void Open() { is_open_ = true; }
    inline void Close() { is_open_ = false; }
    
    inline bool IsLocked() { return is_locked_; }
    inline void Unlock() { is_locked_ = false; }
    
private:
    bool is_open_, is_locked_;
};

typedef std::shared_ptr<Tile> Tile_p;

#endif /* TILE_HPP_ */
