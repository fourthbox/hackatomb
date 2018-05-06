#include "wall_tile.hpp"

#include "game_constants.hpp"
#include "map.hpp"

void WallTile::Draw(TCODConsole &console, bool is_in_fov) {
    assert(initialized_);

    if (is_in_fov || explored_) {
        console.setCharBackground(GetX(), GetY(), kDefaultGroundColor);
        console.setCharForeground(GetX(), GetY(), kDefaultWallColor);
    }
    
    Tile::Draw(console, is_in_fov);
}

void WallTile::Initialize(Map &map) {
    map_ = &map;
    
    initialized_ = true;
}

int WallTile::GetChar() {
    assert(initialized_);
    
    auto bitmask_cmp = [&] (char const &neighbors, char const &figure) -> bool {
        return (neighbors & figure) == figure;
    };
    
    auto x {GetX()}, y {GetY()};
    char neighbors =
    (map_->IsWall(x-1, y-1)?TOP_LEFT_:0) |      (map_->IsWall(x, y-1)?TOP_:0) |         (map_->IsWall(x+1, y-1)?TOP_RIGHT_:0) |
    (map_->IsWall(x-1, y)?LEFT_:0) |                                                    (map_->IsWall(x+1, y)?RIGHT_:0) |
    (map_->IsWall(x-1, y+1)?BOTTOM_LEFT_:0) |   (map_->IsWall(x, y+1)?BOTTOM_:0) |      (map_->IsWall(x+1, y+1)?BOTTOM_RIGHT_:0);
    
    // 8
    if (bitmask_cmp(neighbors, kFullBlock))
        return kCharBlock2;
    
    // 7
    else if (bitmask_cmp(neighbors, kCornerSouthWest))
        return kCharDoubleLineCornerSouthWest;
    else if (bitmask_cmp(neighbors, kCornerNorthWest))
        return kCharDoubleLineCornerNorthWest;
    else if (bitmask_cmp(neighbors, kCornerNorthEast))
        return kCharDoubleLineCornerNorthEast;
    else if (bitmask_cmp(neighbors, kCornerSouthEast))
        return kCharDoubleLineCornerSouthEast;
    
    // 6
    else if (bitmask_cmp(neighbors, kTeeEast4))
        return kCharDoubleLineTeeEast;
    else if (bitmask_cmp(neighbors, kTeeWest4))
        return kCharDoubleLineTeeWest;
    else if (bitmask_cmp(neighbors, kTeeNorth4))
        return kCharDoubleLineTeeNorth;
    else if (bitmask_cmp(neighbors, kTeeSouth4))
        return kCharDoubleLineTeeSouth;
    else if (bitmask_cmp(neighbors, kCenterCross))
        return kCharDoubleLineCross;
    else if (bitmask_cmp(neighbors, kCenterCross2))
        return kCharDoubleLineCross;
    
    // 5
    else if (bitmask_cmp(neighbors, kStraightVertical))
        return kCharDoubleLineVertical;
    else if (bitmask_cmp(neighbors, kStraightVertical2))
        return kCharDoubleLineVertical;
    else if (bitmask_cmp(neighbors, kStraightHorizontal))
        return kCharDoubleLineHorizontal;
    else if (bitmask_cmp(neighbors, kStraightHorizontal2))
        return kCharDoubleLineHorizontal;
    
    // 4
    else if (bitmask_cmp(neighbors, kTeeEast))
        return kCharDoubleLineTeeEast;
    else if (bitmask_cmp(neighbors, kTeeEast2))
        return kCharDoubleLineTeeEast;
    else if (bitmask_cmp(neighbors, kTeeWest))
        return kCharDoubleLineTeeWest;
    else if (bitmask_cmp(neighbors, kTeeWest2))
        return kCharDoubleLineTeeWest;
    else if (bitmask_cmp(neighbors, kTeeNorth))
        return kCharDoubleLineTeeNorth;
    else if (bitmask_cmp(neighbors, kTeeNorth2))
        return kCharDoubleLineTeeNorth;
    else if (bitmask_cmp(neighbors, kTeeSouth))
        return kCharDoubleLineTeeSouth;
    else if (bitmask_cmp(neighbors, kTeeSouth2))
        return kCharDoubleLineTeeSouth;
    else if (bitmask_cmp(neighbors, kCenterCross3))
        return kCharDoubleLineCross;

    // 3
    else if (bitmask_cmp(neighbors, kTeeEast3))
        return kCharDoubleLineTeeEast;
    else if (bitmask_cmp(neighbors, kTeeWest3))
        return kCharDoubleLineTeeWest;
    else if (bitmask_cmp(neighbors, kTeeNorth3))
        return kCharDoubleLineTeeNorth;
    else if (bitmask_cmp(neighbors, kTeeSouth3))
        return kCharDoubleLineTeeSouth;
    
    // 2
    else if (bitmask_cmp(neighbors, kStraightVertical8))
        return kCharDoubleLineVertical;
    else if (bitmask_cmp(neighbors, kStraightHorizontal8))
        return kCharDoubleLineHorizontal;
    else if (bitmask_cmp(neighbors, kCornerSouthWest2))
        return kCharDoubleLineCornerSouthWest;
    else if (bitmask_cmp(neighbors, kCornerNorthWest2))
        return kCharDoubleLineCornerNorthWest;
    else if (bitmask_cmp(neighbors, kCornerNorthEast2))
        return kCharDoubleLineCornerNorthEast;
    else if (bitmask_cmp(neighbors, kCornerSouthEast2))
        return kCharDoubleLineCornerSouthEast;

    // 1
    else if (bitmask_cmp(neighbors, kOpenNorth))
        return kCharDoubleLineOpenNorth;
    else if (bitmask_cmp(neighbors, kOpenSouth))
        return kCharDoubleLineOpenSouth;
    else if (bitmask_cmp(neighbors, kOpenWest))
        return kCharDoubleLineOpenWest;
    else if (bitmask_cmp(neighbors, kOpenEast))
        return kCharDoubleLineOpenEast;
    
    // 0
    else if (bitmask_cmp(neighbors, kEmptyBlock))
        return kCharDoubleLineCenter;
        
    // Default case
    return kCharBlock2;
}
