#include "map.hpp"

#include <cassert>

#include "engine.hpp"
#include "game_constants.hpp"

Map::Map(std::shared_ptr<libpmg::DungeonMap> map) :
    libpmg::DungeonMap {map},
    TCODMap {(int)configs_->map_width_, (int)configs_->map_height_}
{
    Dig();
}

void Map::Dig() {
    for (auto x {0}; x < getWidth(); x++) {
        for (auto y {0}; y < getHeight(); y++) {
            setProperties(x, y, !IsWall(x, y), !IsWall(x, y));
        }
    }
}

int Map::GetWallChar(size_t x, size_t y) {
    assert(IsWall(x, y));
    
    // Count wall tiles
    auto wall_count {0};
    for (auto const &neigh : GetNeighbors(GetTile(x, y), libpmg::MoveDirections::EIGHT_DIRECTIONAL)) {
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

void Map::Draw(ConsoleProxy &console) {
    for (size_t x {0}; x < getWidth(); x++) {
        for (size_t y {0}; y < getHeight(); y++) {
            if (IsWall(x, y)) {
                if (IsInFov(x, y)) {
                    console.SetChar(x, y, GetWallChar(x, y), kDefaultWallInFovColor);
                } else if (IsExplored(x, y)) {
                    console.SetChar(x, y, GetWallChar(x, y), kDefaultWallExploredColor);
                }
            } else {
                if (IsInFov(x, y)) {
                    console.SetChar(x, y, '.', kDefaultGroundInFovColor);
                } else if (IsExplored(x, y)) {
                    console.SetChar(x, y, '.', kDefaultGroundExploredColor);
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

bool Map::IsInFov(size_t x, size_t y) {
#if CHEAT_NO_FOV_
    return true;
#else
    if (isInFov(x, y)) {
        SetExplored(x, y);
        return true;
    }
    
    return false;
#endif
}

void Map::SetExplored(size_t x, size_t y) {
    GetTile(x, y)->AddTag(libpmg::TagManager::GetInstance().explored_tag_);
}

bool Map::IsExplored(size_t x, size_t y) {
    return GetTile(x, y)->HasTag(libpmg::TagManager::GetInstance().explored_tag_);
}
