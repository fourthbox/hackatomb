/**
 Class containing all the constants needed.
 @file game_constants.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef GAME_CONSTANTS_HPP_
#define GAME_CONSTANTS_HPP_

#include "libtcod.hpp"

// TODO: this whole file is deprecated and every constant should be in the header of the most related class

// Colors
static const TCOD_color_t kDefaultGroundColor {TCOD_light_grey};
static const TCOD_color_t kDefaultWallColor {TCOD_darker_grey};
static const TCOD_color_t kDefaultDoorColor {TCOD_sepia};
static const TCOD_color_t kDefaultStairsColor {TCOD_yellow};

static const TCOD_color_t kCorpseColor {TCOD_red};
static const TCOD_color_t kCrosshairColor {TCOD_yellow};

// Frame Sizes
static const size_t kEnvironmentConsoleWidth = 17;
static const size_t kEnvironmentConsoleHeight = 15;
static const size_t kPlayerInfoWindowWidth = 17;
static const size_t kPlayerInfoConsoleHeight = 22;
static const size_t kMessageLogWindowHeight = 6;

static const size_t kMapWidth = 120;
static const size_t kMapHeight = 70;
static const size_t kCameraWidth = 100;
static const size_t kCameraHeight = 50;
static const size_t kRootViewWidth = kCameraWidth + kEnvironmentConsoleWidth + kPlayerInfoWindowWidth;
static const size_t kRootViewHeight = kCameraHeight + kMessageLogWindowHeight;

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

// Sprites
static const int kCharFloor = '.';
static const int kCharClosedDoor = '+';
static const int kCharOpenDoor = '/';
static const int kCharUpstairs = '<';
static const int kCharDownstairs = '>';
static const int kCharHuman = '@';
static const int kCharCorpse = '%';
static const int kCharCrosshair = 'X';

// Keyboard controls
static const char kMoveNorth = 'k';
static const char kMoveNorthEast = 'u';
static const char kMoveEast = 'l';
static const char kMoveSouthEast = 'n';
static const char kMoveSouth = 'j';
static const char kMoveSouthWest = 'b';
static const char kMoveWest = 'h';
static const char kMoveNorthWest = 'y';
static const char kMoveUpstairs = ',';
static const char kMoveDownstairs = '.';
static const char kSkipTurn = '.';

static const char kEnterAimMode = 't';
static const char kOpenInventory = 'i';
static const TCOD_keycode_t kSelectOption = TCODK_ENTER;
static const TCOD_keycode_t kExitMenu = TCODK_ESCAPE;

// Misc constants
static const int kStandardDungeonDepth = 27;
static const int kDefaultFrameRate = 30;

// Map constants
static const size_t kMaxRoomPlacementAttempts = 10;

// Stats constants
static const size_t kMinSpeed = 1;
static const size_t kMaxSpeed = 7;
static const size_t kDodgePointsPerDex = 5;
static const float kDefensePointsPerCon = 0.05f;

#endif /* GAME_CONSTANTS_HPP_ */
