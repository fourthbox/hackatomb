#ifndef WALL_TILE_HPP_
#define WALL_TILE_HPP_

#define TOP_LEFT_        1
#define TOP_             2
#define TOP_RIGHT_       4
#define RIGHT_           8
#define BOTTOM_RIGHT_    16
#define BOTTOM_          32
#define BOTTOM_LEFT_     64
#define LEFT_            128

#include "initiable_object.hpp"
#include "tile.hpp"

class Map;

class WallTile : public Tile, public InitiableObject {
public:
    WallTile(libpmg::Tile *other) : Tile(other) { type_ = TileType::WALL_; }
    void Initialize(Map *map);
    
    void Draw(TCODConsole *console, bool is_in_fov) override;
    
    int GetChar() override;
    inline bool IsTransparent() override { return false; }
    inline bool IsWalkable() override { return false; }
    
private:
    Map *map_;
    
    // 8
    const char kFullBlock =
    TOP_LEFT_ |     TOP_ |      TOP_RIGHT_ |
    LEFT_ |                     RIGHT_ |
    BOTTOM_LEFT_ |  BOTTOM_ |   BOTTOM_RIGHT_;
    
    // 7
    const char kCornerSouthWest =
    TOP_LEFT_ |     TOP_ |      0 |
    LEFT_ |                     RIGHT_ |
    BOTTOM_LEFT_ |  BOTTOM_ |   BOTTOM_RIGHT_;
    
    const char kCornerNorthWest =
    TOP_LEFT_ |     TOP_ |      TOP_RIGHT_ |
    LEFT_ |                     RIGHT_ |
    BOTTOM_LEFT_ |  BOTTOM_ |   0;
    
    const char kCornerNorthEast =
    TOP_LEFT_ |     TOP_ |      TOP_RIGHT_ |
    LEFT_ |                     RIGHT_ |
    0 |  BOTTOM_ |   BOTTOM_RIGHT_;
    
    const char kCornerSouthEast =
    0 |     TOP_ |      TOP_RIGHT_ |
    LEFT_ |                     RIGHT_ |
    BOTTOM_LEFT_ |  BOTTOM_ |   BOTTOM_RIGHT_;

    // 6
    const char kTeeNorth4 =
    0 |     TOP_ |      0 |
    LEFT_ |                     RIGHT_ |
    BOTTOM_LEFT_ |  BOTTOM_ |   BOTTOM_RIGHT_;
    
    const char kTeeSouth4 =
    TOP_LEFT_ |     TOP_ |      TOP_RIGHT_ |
    LEFT_ |                     RIGHT_ |
    0 |  BOTTOM_ |   0;
    
    const char kTeeWest4 =
    0 |     TOP_ |      TOP_RIGHT_ |
    LEFT_ |                     RIGHT_ |
    0 |  BOTTOM_ |   BOTTOM_RIGHT_;
    
    const char kTeeEast4 =
    TOP_LEFT_ |     TOP_ |      0 |
    LEFT_ |                     RIGHT_ |
    BOTTOM_LEFT_ |  BOTTOM_ |   0;
    
    const char kCenterCross =
    0 |     TOP_ |      TOP_RIGHT_ |
    LEFT_ |                     RIGHT_ |
    BOTTOM_LEFT_ |  BOTTOM_ |   0;

    const char kCenterCross2 =
    TOP_LEFT_ |     TOP_ |      0 |
    LEFT_ |                     RIGHT_ |
    0 |  BOTTOM_ |   BOTTOM_RIGHT_;

    // 5
    const char kStraightHorizontal =
    0 |     0 |      0 |
    LEFT_ |                     RIGHT_ |
    BOTTOM_LEFT_ |  BOTTOM_ |   BOTTOM_RIGHT_;

    const char kStraightHorizontal2 =
    TOP_LEFT_ |     TOP_ |      TOP_RIGHT_ |
    LEFT_ |                     RIGHT_ |
    0 |  0 |   0;

    const char kStraightVertical =
    TOP_LEFT_ |     TOP_ |      0 |
    LEFT_ |                     0 |
    BOTTOM_LEFT_ |  BOTTOM_ |   0;

    const char kStraightVertical2 =
    0 |     TOP_ |      TOP_RIGHT_ |
    0 |                     RIGHT_ |
    0 |  BOTTOM_ |   BOTTOM_RIGHT_;
    
    // 4
    const char kTeeSouth =
    0 |     0 |      0 |
    LEFT_ |                     RIGHT_ |
    0 |  BOTTOM_ |   BOTTOM_RIGHT_;

    const char kTeeSouth2 =
    0 |     0 |      0 |
    LEFT_ |                     RIGHT_ |
    BOTTOM_LEFT_ |  BOTTOM_ |   0;

    const char kTeeNorth =
    0 |     TOP_ |      TOP_RIGHT_ |
    LEFT_ |                     RIGHT_ |
    0 |  0 |   0;

    const char kTeeNorth2 =
    TOP_LEFT_ |     TOP_ |      0 |
    LEFT_ |                     RIGHT_ |
    0 |  0 |   0;
    
    const char kTeeEast =
    0 |     TOP_ |      0 |
    0 |                     RIGHT_ |
    0 |  BOTTOM_ |   BOTTOM_RIGHT_;

    const char kTeeEast2 =
    0 |     TOP_ |      TOP_RIGHT_ |
    0 |                     RIGHT_ |
    0 |  BOTTOM_ |   0;

    const char kTeeWest =
    0 |     TOP_ |      0 |
    LEFT_ |                     0 |
    BOTTOM_LEFT_ |  BOTTOM_ |   0;

    const char kTeeWest2 =
    TOP_LEFT_ |     TOP_ |      0 |
    LEFT_ |                     0 |
    0 |  BOTTOM_ |   0;
    
    const char kCenterCross3 =
    0 |     TOP_ |      0 |
    LEFT_ |                     RIGHT_ |
    0 |  BOTTOM_ |   0;
    
    //3
    const char kTeeSouth3 =
    0 |     0 |      0 |
    LEFT_ |                     RIGHT_ |
    0 |  BOTTOM_ |   0;

    const char kTeeNorth3 =
    0 |     TOP_ |      0 |
    LEFT_ |                     RIGHT_ |
    0 |  0 |   0;

    const char kTeeEast3 =
    0 |     TOP_ |      0 |
    0 |                     RIGHT_ |
    0 |  BOTTOM_ |   0;

    const char kTeeWest3 =
    0 |     TOP_ |      0 |
    LEFT_ |                     0 |
    0 |  BOTTOM_ |   0;

    // 2
    const char kStraightHorizontal8 =
    0 |     0 |      0 |
    LEFT_ |                     RIGHT_ |
    0 |  0 |   0;
    
    const char kStraightVertical8 =
    0 |     TOP_ |      0 |
    0 |                     0 |
    0 |  BOTTOM_ |   0;

    const char kCornerSouthEast2 =
    0 |     TOP_ |      0 |
    LEFT_ |                     0 |
    0 |  0 |   0;

    const char kCornerSouthWest2 =
    0 |     TOP_ |      0 |
    0 |                     RIGHT_ |
    0 |  0 |   0;

    const char kCornerNorthWest2 =
    0 |     0 |      0 |
    0 |                     RIGHT_ |
    0 |  BOTTOM_ |   0;

    const char kCornerNorthEast2 =
    0 |     0 |      0 |
    LEFT_ |                     0 |
    0 |  BOTTOM_ |   0;

    // 1
    const char kOpenNorth =
    0 |     0 |      0 |
    0 |                     0 |
    0 |  BOTTOM_ |   0;
    
    const char kOpenEast =
    0 |     0 |      0 |
    LEFT_ |                     0 |
    0 |  0 |   0;

    const char kOpenSouth =
    0 |     TOP_ |      0 |
    0 |                     0 |
    0 |  0 |   0;

    const char kOpenWest =
    0 |     0 |      0 |
    0 |                     RIGHT_ |
    0 |  0 |   0;
    
    // 0
    const char kEmptyBlock =
    0 |     0 |      0 |
    0 |                     0 |
    0 |  0 |   0;


};

#endif /* WALL_TILE_HPP_ */
