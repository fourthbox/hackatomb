#include "wall_tile.hpp"

#include "game_constants.hpp"
#include "map.hpp"

void WallTile::Draw(std::shared_ptr<TCODConsole> console, bool is_in_fov) {
    assert(initialized_);

    if (is_in_fov || explored_) {
        console->setCharBackground(GetX(), GetY(), kDefaultGroundColor);
        console->setCharForeground(GetX(), GetY(), kDefaultWallColor);
    }
    
    Tile::Draw(console, is_in_fov);
}

void WallTile::Initialize(Map *map) {
    map_ = map;
    
    initialized_ = true;
}

int WallTile::GetChar() {
    assert(initialized_);
    
    // Count wall tiles
    auto wall_count {0};
    for (auto const &neigh : map_->GetNeighbors(this)) {
        if (map_->IsWall(neigh))
            wall_count++;
    }
    
    assert (wall_count <= 8);
    
    auto x = GetX(), y = GetY();
    
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
        
        if (map_->IsWall(x-1, y))
            return kCharDoubleLineOpenEast;
        
        if (map_->IsWall(x, y-1))
            return kCharDoubleLineOpenSouth;
        
        if (map_->IsWall(x+1, y))
            return kCharDoubleLineOpenWest;
        
        if (map_->IsWall(x, y+1))
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
        
        if (map_->IsWall(x, y+1) && map_->IsWall(x, y-1))
            return kCharDoubleLineVertical;
        
        if (map_->IsWall(x+1, y) && map_->IsWall(x-1, y))
            return kCharDoubleLineHorizontal;
        
        /**
         .#.        .#.     ...     ...
         .X#        #X.     #X.     .X#
         ...        ...     .#.     .#.
         */
        
        if (map_->IsWall(x+1, y) && map_->IsWall(x, y-1))
            return kCharDoubleLineCornerSouthWest;
        
        if (map_->IsWall(x+1, y) && map_->IsWall(x, y+1) )
            return kCharDoubleLineCornerNorthWest;
        
        if (map_->IsWall(x-1, y) && map_->IsWall(x, y-1))
            return kCharDoubleLineCornerSouthEast;
        
        if (map_->IsWall(x-1, y) && map_->IsWall(x, y+1))
            return kCharDoubleLineCornerNorthEast;
        
        /**
         ...    .#.     ...     ...
         #X.    .X.     .X#     .X.
         ...    ...     ...     .#.
         */
        
        if (map_->IsWall(x-1, y))
            return kCharDoubleLineOpenEast;
        
        if (map_->IsWall(x, y-1))
            return kCharDoubleLineOpenSouth;
        
        if (map_->IsWall(x+1, y))
            return kCharDoubleLineOpenWest;
        
        if (map_->IsWall(x, y+1))
            return kCharDoubleLineOpenNorth;
        
    }
    if (wall_count == 3) {
        /**
         .#.        .#.     ...     .#.
         .X#        #X.     #X#     #X#
         .#.        .#.     .#.     ...
         */
        
        if (map_->IsWall(x, y-1) && map_->IsWall(x+1, y) && map_->IsWall(x, y+1))
            return kCharDoubleLineTeeEast;
        
        if (map_->IsWall(x, y-1) && map_->IsWall(x-1, y) && map_->IsWall(x, y+1))
            return kCharDoubleLineTeeWest;
        
        if (map_->IsWall(x-1, y) && map_->IsWall(x+1, y) && map_->IsWall(x, y+1))
            return kCharDoubleLineTeeSouth;
        
        if (map_->IsWall(x, y-1) && map_->IsWall(x-1, y) && map_->IsWall(x+1, y))
            return kCharDoubleLineTeeNorth;
        
        /**
         .#.        ...
         .X.        #X#
         .#.        ...
         */
        
        if (map_->IsWall(x, y+1) && map_->IsWall(x, y-1))
            return kCharDoubleLineVertical;
        
        if (map_->IsWall(x+1, y) && map_->IsWall(x-1, y))
            return kCharDoubleLineHorizontal;
        
        /**
         .#.        .#.     ...     ...
         .X#        #X.     #X.     .X#
         ...        ...     .#.     .#.
         */
        
        if (map_->IsWall(x+1, y) && map_->IsWall(x, y-1))
            return kCharDoubleLineCornerSouthWest;
        
        if (map_->IsWall(x+1, y) && map_->IsWall(x, y+1))
            return kCharDoubleLineCornerNorthWest;
        
        if (map_->IsWall(x-1, y) && map_->IsWall(x, y-1))
            return kCharDoubleLineCornerSouthEast;
        
        if (map_->IsWall(x-1, y) && map_->IsWall(x, y+1))
            return kCharDoubleLineCornerNorthEast;
        
        /**
         ...    .#.     ...     ...
         #X.    .X.     .X#     .X.
         ...    ...     ...     .#.
         */
        
        if (map_->IsWall(x-1, y))
            return kCharDoubleLineOpenEast;
        
        if (map_->IsWall(x, y-1))
            return kCharDoubleLineOpenSouth;
        
        if (map_->IsWall(x+1, y))
            return kCharDoubleLineOpenWest;
        
        if (map_->IsWall(x, y+1))
            return kCharDoubleLineOpenNorth;
        
    }
    if (wall_count == 4)
    {
        /**
         .#.
         #X#
         .#.
         */
        
        if (map_->IsWall(x, y-1) &&
            map_->IsWall(x-1, y) &&
            map_->IsWall(x+1, y) &&
            map_->IsWall(x, y+1))
            return kCharDoubleLineCross;
        
        /**
         .#.        .#.     ...     .#.
         .X#        #X.     #X#     #X#
         .#.        .#.     .#.     ...
         */
        
        if (map_->IsWall(x+1, y) && map_->IsWall(x, y+1) && map_->IsWall(x, y-1))
            return kCharDoubleLineTeeEast;
        
        if (map_->IsWall(x-1, y) && map_->IsWall(x, y-1) && map_->IsWall(x, y+1))
            return kCharDoubleLineTeeWest;
        
        if (map_->IsWall(x-1, y) && map_->IsWall(x+1, y) && map_->IsWall(x, y+1))
            return kCharDoubleLineTeeSouth;
        
        if (map_->IsWall(x-1, y) && map_->IsWall(x+1, y) && map_->IsWall(x, y-1))
            return kCharDoubleLineTeeNorth;
        
        /**
         .#.        ...
         .X.        #X#
         .#.        ...
         */
        
        if (map_->IsWall(x, y+1) && map_->IsWall(x, y-1))
            return kCharDoubleLineVertical;
        
        if (map_->IsWall(x+1, y) && map_->IsWall(x-1, y))
            return kCharDoubleLineHorizontal;
        
        /**
         .#.        .#.     ...     ...
         .X#        #X.     #X.     .X#
         ...        ...     .#.     .#.
         */
        
        if (map_->IsWall(x+1, y) && map_->IsWall(x, y-1))
            return kCharDoubleLineCornerSouthWest;
        
        if (map_->IsWall(x+1, y) && map_->IsWall(x, y+1))
            return kCharDoubleLineCornerNorthWest;
        
        if (map_->IsWall(x-1, y) && map_->IsWall(x, y-1))
            return kCharDoubleLineCornerSouthEast;
        
        if (map_->IsWall(x-1, y) && map_->IsWall(x, y+1))
            return kCharDoubleLineCornerNorthEast;
        
    }
    if (wall_count == 5)
    {
        /**
         .#.        .#.     ...     ...
         .X#        #X.     #X.     .X#
         ...        ...     .#.     .#.
         */
        
        if (!map_->IsWall(x-1, y) && !map_->IsWall(x, y+1))
            return kCharDoubleLineCornerSouthWest;
        
        if (!map_->IsWall(x-1, y) && !map_->IsWall(x, y-1))
            return kCharDoubleLineCornerNorthWest;
        
        if (!map_->IsWall(x+1, y) && !map_->IsWall(x, y+1))
            return kCharDoubleLineCornerSouthEast;
        
        if (!map_->IsWall(x+1, y) && !map_->IsWall(x, y-1))
            return kCharDoubleLineCornerNorthEast;
        
        /**
         ###        ###     .#.        .#.
         .X#        #X.     .X#        #X.
         .#.        .#.     ###        ###
         */
        
        if (!map_->IsWall(x-1, y) && !map_->IsWall(x-1, y+1) && !map_->IsWall(x+1, y+1))
            return kCharDoubleLineTeeEast;
        
        if (!map_->IsWall(x+1, y) && !map_->IsWall(x-1, y+1) && !map_->IsWall(x+1, y+1))
            return kCharDoubleLineTeeWest;
        
        if (!map_->IsWall(x-1, y-1) && !map_->IsWall(x+1, y-1) && !map_->IsWall(x-1, y))
            return kCharDoubleLineTeeEast;
        
        if (!map_->IsWall(x-1, y-1) && !map_->IsWall(x+1, y-1) && !map_->IsWall(x+1, y))
            return kCharDoubleLineTeeWest;
        
        /**
         ##.        #..     .##        ..#
         #X#        #X#     #X#        #X#
         #..        ##.     ..#        .##
         */
        
        if (!map_->IsWall(x+1, y-1) && !map_->IsWall(x, y+1) && !map_->IsWall(x+1, y+1))
            return kCharDoubleLineTeeNorth;
        
        if (!map_->IsWall(x, y-1) && !map_->IsWall(x+1, y-1) && !map_->IsWall(x+1, y+1))
            return kCharDoubleLineTeeSouth;
        
        if (!map_->IsWall(x-1, y-1) && !map_->IsWall(x-1, y+1) && !map_->IsWall(x, y+1))
            return kCharDoubleLineTeeNorth;
        
        if (!map_->IsWall(x-1, y-1) && !map_->IsWall(x, y-1) && !map_->IsWall(x-1, y+1))
            return kCharDoubleLineTeeSouth;
        
        /**
         ##.        .##     ...        ###
         #X.        .X#     #X#        #X#
         ##.        .##     ###        ...
         */
        
        if (!map_->IsWall(x+1, y-1) && !map_->IsWall(x+1, y) && !map_->IsWall(x+1, y+1))
            return kCharDoubleLineVertical;
        
        if (!map_->IsWall(x-1, y-1) && !map_->IsWall(x-1, y) && !map_->IsWall(x-1, y+1))
            return kCharDoubleLineVertical;
        
        if (!map_->IsWall(x-1, y-1) && !map_->IsWall(x, y-1) && !map_->IsWall(x+1, y-1))
            return kCharDoubleLineHorizontal;
        
        if (!map_->IsWall(x-1, y+1) && !map_->IsWall(x, y+1) && !map_->IsWall(x+1, y+1))
            return kCharDoubleLineHorizontal;
        
        
        /**
         .#.        .#.     ...     .#.
         .X#        #X.     #X#     #X#
         .#.        .#.     .#.     ...
         */
        
        if (!map_->IsWall(x-1, y))
            return kCharDoubleLineTeeEast;
        
        if (!map_->IsWall(x+1, y))
            return kCharDoubleLineTeeWest;
        
        if (!map_->IsWall(x, y-1))
            return kCharDoubleLineTeeSouth;
        
        if (!map_->IsWall(x, y+1))
            return kCharDoubleLineTeeNorth;
        
        /**
         .#.
         #X#
         .#.
         */
        
        if (map_->IsWall(x, y-1) &&
            map_->IsWall(x-1, y) &&
            map_->IsWall(x+1, y) &&
            map_->IsWall(x, y+1))
            return kCharDoubleLineCross;
        
    }
    if (wall_count == 6)
    {
        /**
         .##        ##.
         #X#        #X#
         ##.        .##
         */
        
        if ((!map_->IsWall(x-1, y-1) && !map_->IsWall(x+1, y+1))
            || (!map_->IsWall(x+1, y-1) && !map_->IsWall(x-1, y+1)))
            return kCharDoubleLineCross;
        
        /**
         ##.        .#.     .##     ###
         #X#        #X#     #X#     #X#
         ##.        ###     .##     .#.
         */
        
        if (!map_->IsWall(x+1, y-1) && !map_->IsWall(x+1, y+1))
            return kCharDoubleLineTeeEast;
        
        if (!map_->IsWall(x-1, y-1) && !map_->IsWall(x+1, y-1))
            return kCharDoubleLineTeeNorth;
        
        if (!map_->IsWall(x-1, y-1) && !map_->IsWall(x-1, y+1))
            return kCharDoubleLineTeeWest;
        
        if (!map_->IsWall(x-1, y+1) && !map_->IsWall(x+1, y+1))
            return kCharDoubleLineTeeSouth;
        
        /**
         .#.        ...
         .X.        #X#
         .#.        ...
         */
        
        if (map_->IsWall(x, y-1) && map_->IsWall(x, y+1))
            return kCharDoubleLineVertical;
        
        if (map_->IsWall(x-1, y) && map_->IsWall(x+1, y))
            return kCharDoubleLineHorizontal;
        
        /**
         .#.        .#.     ...     .#.
         .X#        #X.     #X#     #X#
         .#.        .#.     .#.     ...
         */
        
        if (!map_->IsWall(x-1, y))
            return kCharDoubleLineTeeEast;
        
        if (!map_->IsWall(x+1, y))
            return kCharDoubleLineTeeWest;
        
        if (!map_->IsWall(x, y-1))
            return kCharDoubleLineTeeSouth;
        
        if (!map_->IsWall(x, y+1))
            return kCharDoubleLineTeeNorth;
    }
    if (wall_count == 7)
    {
        /**
         ##.    .##     ###     ###
         #X#    #X#     #X#     #X#
         ###    ###     .##     ##.
         */
        
        if (!map_->IsWall(x+1, y-1))
            return kCharDoubleLineCornerSouthWest;
        
        if (!map_->IsWall(x-1, y-1))
            return kCharDoubleLineCornerSouthEast;
        
        if (!map_->IsWall(x-1, y+1))
            return kCharDoubleLineCornerNorthEast;
        
        if (!map_->IsWall(x+1, y+1))
            return kCharDoubleLineCornerNorthWest;
    }
    
    // Default case
    return kCharBlock2;
}
