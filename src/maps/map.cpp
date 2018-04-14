#include "map.hpp"

#include <cassert>

#include "engine.hpp"
#include "game_constants.hpp"

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
    map_configs_ = map.GetConfigs();
    for (auto const &tile : map.GetMap()) {
        map_.push_back(std::make_shared<Tile>(tile));
    }
}

std::vector<Tile_p> Map::GetNeighbors(Tile_p tile) {
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

int Map::GetWallChar(size_t x, size_t y) {
    assert(IsWall(x, y));
    
    // Count wall tiles
    auto wall_count {0};
    for (auto const &neigh : GetNeighbors(GetTile(x, y))) {
        if (IsWall(neigh->GetX(), neigh->GetY()))
            wall_count++;
    }

    assert (wall_count <= 8);
    
    // Block check
    if (wall_count == 8)
        return kCharBlock2;
    // Center block
    if (wall_count == 0)
        return kCharDoubleLineCenter;
    if (wall_count == 1) {
        /**
             ...    .#.     ...     ...
             #X.    .X.     .X#     .X.
             ...    ...     ...     .#.
         */
        
        if (IsWall(x-1, y))
            return kCharDoubleLineOpenEast;
        
        if (IsWall(x, y-1))
            return kCharDoubleLineOpenSouth;
        
        if (IsWall(x+1, y))
            return kCharDoubleLineOpenWest;
        
        if (IsWall(x, y+1))
            return kCharDoubleLineOpenNorth;
        
        /**
             #..    ..#     ...     ...
             .X.    .X.     .X.     .X.
             ...    ...     ..#     #..
         */
        
        return kCharDoubleLineCenter;
    }
    if (wall_count == 2) {
        
        /**
             .#.        ...
             .X.        #X#
             .#.        ...
         */
        
        if (IsWall(x, y+1) && IsWall(x, y-1))
            return kCharDoubleLineVertical;
        
        if (IsWall(x+1, y) && IsWall(x-1, y))
            return kCharDoubleLineHorizontal;
        
        /**
             .#.        .#.     ...     ...
             .X#        #X.     #X.     .X#
             ...        ...     .#.     .#.
         */
        
        if (IsWall(x+1, y) && IsWall(x, y-1))
            return kCharDoubleLineCornerSouthWest;

        if (IsWall(x+1, y) && IsWall(x, y+1) )
            return kCharDoubleLineCornerNorthWest;

        if (IsWall(x-1, y) && IsWall(x, y-1))
            return kCharDoubleLineCornerSouthEast;

        if (IsWall(x-1, y) && IsWall(x, y+1))
            return kCharDoubleLineCornerNorthEast;
        
        /**
             ...    .#.     ...     ...
             #X.    .X.     .X#     .X.
             ...    ...     ...     .#.
         */
        
        if (IsWall(x-1, y))
            return kCharDoubleLineOpenEast;

        if (IsWall(x, y-1))
            return kCharDoubleLineOpenSouth;

        if (IsWall(x+1, y))
            return kCharDoubleLineOpenWest;

        if (IsWall(x, y+1))
            return kCharDoubleLineOpenNorth;

    }
    if (wall_count == 3) {
        /**
             .#.        .#.     ...     .#.
             .X#        #X.     #X#     #X#
             .#.        .#.     .#.     ...
         */
        
        if (IsWall(x, y-1) && IsWall(x+1, y) && IsWall(x, y+1))
            return kCharDoubleLineTeeEast;
        
        if (IsWall(x, y-1) && IsWall(x-1, y) && IsWall(x, y+1))
            return kCharDoubleLineTeeWest;

        if (IsWall(x-1, y) && IsWall(x+1, y) && IsWall(x, y+1))
            return kCharDoubleLineTeeSouth;

        if (IsWall(x, y-1) && IsWall(x-1, y) && IsWall(x+1, y))
            return kCharDoubleLineTeeNorth;
        
        /**
             .#.        ...
             .X.        #X#
             .#.        ...
         */

        if (IsWall(x, y+1) && IsWall(x, y-1))
            return kCharDoubleLineVertical;
        
        if (IsWall(x+1, y) && IsWall(x-1, y))
            return kCharDoubleLineHorizontal;
        
        /**
             .#.        .#.     ...     ...
             .X#        #X.     #X.     .X#
             ...        ...     .#.     .#.
         */
        
        if (IsWall(x+1, y) && IsWall(x, y-1))
            return kCharDoubleLineCornerSouthWest;

        if (IsWall(x+1, y) && IsWall(x, y+1))
            return kCharDoubleLineCornerNorthWest;

        if (IsWall(x-1, y) && IsWall(x, y-1))
            return kCharDoubleLineCornerSouthEast;

        if (IsWall(x-1, y) && IsWall(x, y+1))
            return kCharDoubleLineCornerNorthEast;
        
        /**
             ...    .#.     ...     ...
             #X.    .X.     .X#     .X.
             ...    ...     ...     .#.
         */
        
        if (IsWall(x-1, y))
            return kCharDoubleLineOpenEast;
        
        if (IsWall(x, y-1))
            return kCharDoubleLineOpenSouth;
        
        if (IsWall(x+1, y))
            return kCharDoubleLineOpenWest;
        
        if (IsWall(x, y+1))
            return kCharDoubleLineOpenNorth;

    }
    if (wall_count == 4)
    {
        /**
             .#.
             #X#
             .#.
         */
        
        if (IsWall(x, y-1) &&
            IsWall(x-1, y) &&
            IsWall(x+1, y) &&
            IsWall(x, y+1))
            return kCharDoubleLineCross;

        /**
             .#.        .#.     ...     .#.
             .X#        #X.     #X#     #X#
             .#.        .#.     .#.     ...
         */
        
        if (IsWall(x+1, y) && IsWall(x, y+1) && IsWall(x, y-1))
            return kCharDoubleLineTeeEast;
        
        if (IsWall(x-1, y) && IsWall(x, y-1) && IsWall(x, y+1))
            return kCharDoubleLineTeeWest;
        
        if (IsWall(x-1, y) && IsWall(x+1, y) && IsWall(x, y+1))
            return kCharDoubleLineTeeSouth;
        
        if (IsWall(x-1, y) && IsWall(x+1, y) && IsWall(x, y-1))
            return kCharDoubleLineTeeNorth;

        /**
             .#.        ...
             .X.        #X#
             .#.        ...
         */
        
        if (IsWall(x, y+1) && IsWall(x, y-1))
            return kCharDoubleLineVertical;

        if (IsWall(x+1, y) && IsWall(x-1, y))
            return kCharDoubleLineHorizontal;
        
        /**
             .#.        .#.     ...     ...
             .X#        #X.     #X.     .X#
             ...        ...     .#.     .#.
         */
        
        if (IsWall(x+1, y) && IsWall(x, y-1))
            return kCharDoubleLineCornerSouthWest;
        
        if (IsWall(x+1, y) && IsWall(x, y+1))
            return kCharDoubleLineCornerNorthWest;
        
        if (IsWall(x-1, y) && IsWall(x, y-1))
            return kCharDoubleLineCornerSouthEast;
        
        if (IsWall(x-1, y) && IsWall(x, y+1))
            return kCharDoubleLineCornerNorthEast;

    }
    if (wall_count == 5)
    {
        /**
             .#.        .#.     ...     ...
             .X#        #X.     #X.     .X#
             ...        ...     .#.     .#.
         */
        
        if (!IsWall(x-1, y) && !IsWall(x, y+1))
            return kCharDoubleLineCornerSouthWest;
        
        if (!IsWall(x-1, y) && !IsWall(x, y-1))
            return kCharDoubleLineCornerNorthWest;
        
        if (!IsWall(x+1, y) && !IsWall(x, y+1))
            return kCharDoubleLineCornerSouthEast;
        
        if (!IsWall(x+1, y) && !IsWall(x, y-1))
            return kCharDoubleLineCornerNorthEast;
        
        /**
             ###        ###     .#.        .#.
             .X#        #X.     .X#        #X.
             .#.        .#.     ###        ###
         */
        
        if (!IsWall(x-1, y) && !IsWall(x-1, y+1) && !IsWall(x+1, y+1))
            return kCharDoubleLineTeeEast;
        
        if (!IsWall(x+1, y) && !IsWall(x-1, y+1) && !IsWall(x+1, y+1))
            return kCharDoubleLineTeeWest;

        if (!IsWall(x-1, y-1) && !IsWall(x+1, y-1) && !IsWall(x-1, y))
            return kCharDoubleLineTeeEast;

        if (!IsWall(x-1, y-1) && !IsWall(x+1, y-1) && !IsWall(x+1, y))
            return kCharDoubleLineTeeWest;
        
        /**
             ##.        #..     .##        ..#
             #X#        #X#     #X#        #X#
             #..        ##.     ..#        .##
         */
        
        if (!IsWall(x+1, y-1) && !IsWall(x, y+1) && !IsWall(x+1, y+1))
            return kCharDoubleLineTeeNorth;
        
        if (!IsWall(x, y-1) && !IsWall(x+1, y-1) && !IsWall(x+1, y+1))
            return kCharDoubleLineTeeSouth;
        
        if (!IsWall(x-1, y-1) && !IsWall(x-1, y+1) && !IsWall(x, y+1))
            return kCharDoubleLineTeeNorth;
        
        if (!IsWall(x-1, y-1) && !IsWall(x, y-1) && !IsWall(x-1, y+1))
            return kCharDoubleLineTeeSouth;
        
        /**
             ##.        .##     ...        ###
             #X.        .X#     #X#        #X#
             ##.        .##     ###        ...
         */
        
        if (!IsWall(x+1, y-1) && !IsWall(x+1, y) && !IsWall(x+1, y+1))
            return kCharDoubleLineVertical;
        
        if (!IsWall(x-1, y-1) && !IsWall(x-1, y) && !IsWall(x-1, y+1))
            return kCharDoubleLineVertical;
        
        if (!IsWall(x-1, y-1) && !IsWall(x, y-1) && !IsWall(x+1, y-1))
            return kCharDoubleLineHorizontal;
        
        if (!IsWall(x-1, y+1) && !IsWall(x, y+1) && !IsWall(x+1, y+1))
            return kCharDoubleLineHorizontal;


        /**
             .#.        .#.     ...     .#.
             .X#        #X.     #X#     #X#
             .#.        .#.     .#.     ...
         */
        
        if (!IsWall(x-1, y))
            return kCharDoubleLineTeeEast;

        if (!IsWall(x+1, y))
            return kCharDoubleLineTeeWest;

        if (!IsWall(x, y-1))
            return kCharDoubleLineTeeSouth;

        if (!IsWall(x, y+1))
            return kCharDoubleLineTeeNorth;
        
        /**
             .#.
             #X#
             .#.
         */
        
        if (IsWall(x, y-1) &&
            IsWall(x-1, y) &&
            IsWall(x+1, y) &&
            IsWall(x, y+1))
            return kCharDoubleLineCross;

    }
    if (wall_count == 6)
    {
        /**
             .##        ##.
             #X#        #X#
             ##.        .##
         */
        
        if ((!IsWall(x-1, y-1) && !IsWall(x+1, y+1))
            || (!IsWall(x+1, y-1) && !IsWall(x-1, y+1)))
            return kCharDoubleLineCross;

        /**
             ##.        .#.     .##     ###
             #X#        #X#     #X#     #X#
             ##.        ###     .##     .#.
         */
        
        if (!IsWall(x+1, y-1) && !IsWall(x+1, y+1))
            return kCharDoubleLineTeeEast;
        
        if (!IsWall(x-1, y-1) && !IsWall(x+1, y-1))
            return kCharDoubleLineTeeNorth;
        
        if (!IsWall(x-1, y-1) && !IsWall(x-1, y+1))
            return kCharDoubleLineTeeWest;
        
        if (!IsWall(x-1, y+1) && !IsWall(x+1, y+1))
            return kCharDoubleLineTeeSouth;

        /**
             .#.        ...
             .X.        #X#
             .#.        ...
         */
        
        if (IsWall(x, y-1) && IsWall(x, y+1))
            return kCharDoubleLineVertical;
        
        if (IsWall(x-1, y) && IsWall(x+1, y))
            return kCharDoubleLineHorizontal;

        /**
             .#.        .#.     ...     .#.
             .X#        #X.     #X#     #X#
             .#.        .#.     .#.     ...
         */
        
        if (!IsWall(x-1, y))
            return kCharDoubleLineTeeEast;
        
        if (!IsWall(x+1, y))
            return kCharDoubleLineTeeWest;
        
        if (!IsWall(x, y-1))
            return kCharDoubleLineTeeSouth;
        
        if (!IsWall(x, y+1))
            return kCharDoubleLineTeeNorth;
    }
    if (wall_count == 7)
    {
        /**
             ##.    .##     ###     ###
             #X#    #X#     #X#     #X#
             ###    ###     .##     ##.
         */
        
        if (!IsWall(x+1, y-1))
            return kCharDoubleLineCornerSouthWest;
        
        if (!IsWall(x-1, y-1))
            return kCharDoubleLineCornerSouthEast;
        
        if (!IsWall(x-1, y+1))
            return kCharDoubleLineCornerNorthEast;
        
        if (!IsWall(x+1, y+1))
            return kCharDoubleLineCornerNorthWest;
    }

    // Default case
    return kCharBlock2;
}

void Map::Draw(std::shared_ptr<TCODConsole> console) {
    for (size_t x {0}; x < getWidth(); x++) {
        for (size_t y {0}; y < getHeight(); y++) {
            // Wall
            if (IsWall(x, y)) {
                if (IsInFov(x, y)) {
                    console->setChar(x, y, GetWallChar(x, y));
                    console->setCharForeground(x, y, kDefaultWallInFovColor);
                } else if (IsExplored(x, y)) {
                    console->setChar(x, y, GetWallChar(x, y));
                    console->setCharForeground(x, y, kDefaultWallExploredColor);
                }
            } else if (HasDoor(x, y)) {
                // Door
                
            } else {
                // Empty
                if (IsInFov(x, y)) {
                    console->setChar(x, y, '.');
                    console->setCharForeground(x, y, kDefaultGroundInFovColor);
                } else if (IsExplored(x, y)) {
                    console->setChar(x, y, '.');
                    console->setCharForeground(x, y, kDefaultGroundExploredColor);
                }
            }
        }
    }    
}

bool Map::IsWall(size_t x, size_t y) {
    auto tile {GetTile(x, y)};
    
    if (tile == nullptr)
        return false;
    
    return tile->HasTag(libpmg::TagManager::GetInstance().wall_tag_);
}

bool Map::HasDoor(size_t x, size_t y) {
    auto tile {GetTile(x, y)};
    
    if (tile == nullptr)
        return false;
    
    return tile->HasTag(libpmg::TagManager::GetInstance().door_tag_);
}

bool Map::IsInFov(size_t x, size_t y) {
    if (isInFov(x, y)) {
        SetExplored(x, y);
        return true;
    }
    
    return false;
}

Tile_p Map::GetTile(size_t x, size_t y) {
    assert(map_configs_ != nullptr);

    if (!BoundsCheck(x, y))
        return nullptr;
    
    return map_[y * map_configs_->map_width_ + x];
}

bool Map::BoundsCheck(std::size_t x, std::size_t y) {
    assert(map_configs_ != nullptr);
    
    return x < map_configs_->map_width_ && y < map_configs_->map_height_;
}

void Map::SetExplored(size_t x, size_t y) {
    GetTile(x, y)->AddTag(libpmg::TagManager::GetInstance().explored_tag_);
}

bool Map::IsExplored(size_t x, size_t y) {
    return GetTile(x, y)->HasTag(libpmg::TagManager::GetInstance().explored_tag_);
}

void Map::SetAllExplored() {
    for (size_t x {0}; x < getWidth(); x++) {
        for (size_t y {0}; y < getHeight(); y++) {
            SetExplored(x, y);
        }
    }
}

