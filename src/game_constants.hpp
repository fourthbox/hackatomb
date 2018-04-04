/**
 Class containing all the constants needed.
 @file game_constants.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef GAME_CONSTANTS_HPP_
#define GAME_CONSTANTS_HPP_

static const TCOD_color_t kDefaultGroundInFovColor {TCOD_light_sepia};
static const TCOD_color_t kDefaultGroundExploredColor {TCOD_darkest_sepia};
static const TCOD_color_t kDefaultWallInFovColor {TCOD_light_grey};
static const TCOD_color_t kDefaultWallExploredColor {TCOD_darkest_grey};

static const size_t kEnvironmentConsoleWidth = 17;
static const size_t kEnvironmentConsoleHeight = 15;
static const size_t kPlayerInfoConsoleWidth = 17;
static const size_t kPlayerInfoConsoleHeight = 22;
static const size_t kMessageLogConsoleHeight = 6;

static const size_t kMapWidth = 100;
static const size_t kMapHeight = 50;
static const size_t kRootViewWidth = kMapWidth + kEnvironmentConsoleWidth + kPlayerInfoConsoleWidth;
static const size_t kRootViewHeight = kMapHeight + kMessageLogConsoleHeight;

// Characher mappings
static const int kCharEmpty = 0;
static const int kCharBulletSquare = TCOD_CHAR_BULLET_SQUARE;

static const int kCharDoubleLineHorizontal = TCOD_CHAR_DHLINE;
static const int kCharDoubleLineVertical = TCOD_CHAR_DVLINE;

static const int kCharDoubleLineCornerNorthEast = TCOD_CHAR_DNE;
static const int kCharDoubleLineCornerSouthEast = TCOD_CHAR_DSE;
static const int kCharDoubleLineCornerSouthWest = TCOD_CHAR_DSW;
static const int kCharDoubleLineCornerNorthWest = TCOD_CHAR_DNW;

static const int kCharDoubleLineTeeNorth = TCOD_CHAR_DTEEN;
static const int kCharDoubleLineTeeEast = TCOD_CHAR_DTEEE;
static const int kCharDoubleLineTeeSouth = TCOD_CHAR_DTEES;
static const int kCharDoubleLineTeeWest = TCOD_CHAR_DTEEW;

static const int kCharDoubleLineOpenNorth = 226;
static const int kCharDoubleLineOpenEast = 227;
static const int kCharDoubleLineOpenSouth = 228;
static const int kCharDoubleLineOpenWest = 229;

static const int kCharDoubleLineCenter = 230;
static const int kCharDoubleLineCross = TCOD_CHAR_DCROSS;

static const int kCharBlock2 = TCOD_CHAR_BLOCK2;

// Keyboard controls
static const char kMoveNorth = 'k';
static const char kMoveNorthEast = 'u';
static const char kMoveEast = 'l';
static const char kMoveSouthEast = 'n';
static const char kMoveSouth = 'j';
static const char kMoveSouthWest = 'b';
static const char kMoveWest = 'h';
static const char kMoveNorthWest = 'y';

#endif /* GAME_CONSTANTS_HPP_ */
