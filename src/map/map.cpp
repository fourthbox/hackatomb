#include "map.hpp"

#include <cassert>

#include "door_tile.hpp"
#include "empty_tile.hpp"
#include "engine.hpp"
#include "game_utils.hpp"
#include "wall_tile.hpp"

Map::Map(libpmg::DungeonMap &map) :
TCODMap {(int)map.GetConfigs()->map_width_, (int)map.GetConfigs()->map_height_} {
    DigPmgMap(map);
    DigTcodMap();
}

void Map::DigTcodMap() {
    for (auto x {0}; x < getWidth(); x++) {
        for (auto y {0}; y < getHeight(); y++) {
            setProperties(x, y, !IsWall(x, y), !IsWall(x, y));
        }
    }
}

void Map::DigPmgMap(libpmg::DungeonMap &map) {
    map_configs_ = *map.GetConfigs();
    
    for (auto const &tile : map.GetMap()) {
        
        if (tile->HasTag(libpmg::TagManager::GetInstance().wall_tag_)) {
            auto new_tile {std::make_shared<WallTile>(tile)};
            new_tile->Initialize(this);
            map_.push_back(new_tile);
        } else if (tile->HasTag(libpmg::TagManager::GetInstance().door_tag_)) {
            map_.push_back(std::make_shared<DoorTile>(tile));
        } else if (tile->HasTag(libpmg::TagManager::GetInstance().floor_tag_)) {
            map_.push_back(std::make_shared<EmptyTile>(tile));
        } else {
            Utils::LogError("Map", "Unrecognized tag.");
            abort();
        }
    }
}

std::vector<Tile_p> Map::GetNeighbors(Tile *tile) {
    size_t x, y;
    std::tie(x, y) = tile->GetXY();
    std::vector<Tile_p> vec;
    
    if (auto tile {GetTile(x, y-1)}; tile != nullptr)
        vec.push_back(tile);
    if (auto tile {GetTile(x+1, y)}; tile != nullptr)
        vec.push_back(tile);
    if (auto tile {GetTile(x, y+1)}; tile != nullptr)
        vec.push_back(tile);
    if (auto tile {GetTile(x-1, y)}; tile != nullptr)
        vec.push_back(tile);
    
    if (auto tile {GetTile(x-1, y-1)}; tile != nullptr)
        vec.push_back(tile);
    if (auto tile {GetTile(x+1, y+1)}; tile != nullptr)
        vec.push_back(tile);
    if (auto tile {GetTile(x-1, y+1)}; tile != nullptr)
        vec.push_back(tile);
    if (auto tile {GetTile(x+1, y-1)}; tile != nullptr)
        vec.push_back(tile);
    
    return vec;
}

void Map::Draw(std::shared_ptr<TCODConsole> console) {
    for (auto const &tile : map_) {
        tile->Draw(console, IsInFov(tile->GetX(), tile->GetY()));
    }
    
    return;
}

bool Map::IsWall(size_t x, size_t y) {
    auto tile {GetTile(x, y)};
    
    if (tile == nullptr)
        return false;
    
    return (tile->GetType() == TileType::WALL_);
}

bool Map::IsWall(Tile_p tile) {    
    return (tile->GetType() == TileType::WALL_);
}

bool Map::HasDoor(size_t x, size_t y) {
    auto tile {GetTile(x, y)};
    
    if (tile == nullptr)
        return false;
    
    return (tile->GetType() == TileType::DOOR_);
}

bool Map::IsInFov(size_t x, size_t y) {
    if (isInFov(x, y)) {
        SetExplored(x, y);
        return true;
    }
    
    return false;
}

Tile_p Map::GetTile(size_t x, size_t y) {
    if (!BoundsCheck(x, y))
        return nullptr;
    
    return map_[y * map_configs_.map_width_ + x];
}

bool Map::BoundsCheck(std::size_t x, std::size_t y) {    
    return x < map_configs_.map_width_ && y < map_configs_.map_height_;
}

void Map::SetExplored(size_t x, size_t y) {
    GetTile(x, y)->Explore();
}

bool Map::IsExplored(size_t x, size_t y) {
    return GetTile(x, y)->IsExplored();
}

void Map::SetAllExplored() {
    for (size_t x {0}; x < getWidth(); x++) {
        for (size_t y {0}; y < getHeight(); y++) {
            SetExplored(x, y);
        }
    }
}

