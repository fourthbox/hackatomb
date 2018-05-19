#include "dungeon_factory.hpp"

#include "game_constants.hpp"
#include "game_globals.hpp"

// Normal
static const size_t kMinRoomSizeWidthNormal =                         4;
static const size_t kMinRoomSizeHeightNormal =                        4;
static const size_t kMaxRoomSizeWidthNormal =                         12;
static const size_t kMaxRoomSizeHeightNormal =                        12;
static const size_t kMaxRoomsNormal =                                 5;
static const libpmg::PathAlgorithm kDefaultPathAlgorithmNormal =      libpmg::PathAlgorithm::ASTAR_BFS_MIX;
static const bool kDiagonalCorridorsNormal =                          false;

static const size_t kMinUpstairsAmountNormal =                        1;
static const size_t kMaxUpstairsAmountNormal =                        1;
static const size_t kMinDownstairsAmountNormal =                      1;
static const size_t kMaxDownstairsAmountNormal =                      1;
static const bool kDigAroundStairsNormal =                            false;
static const bool kDigStairsOnlyInRoomsNormal =                       true;

DungeonFactory::DungeonFactory() {

    // Initialize the normal dungeon builder
    category_builders_[DungeonCategory::NORMAL_] = std::make_unique<libpmg::DungeonBuilder>();
}

void DungeonFactory::SetupBuilder(libpmg::DungeonBuilder &builder) {
    builder.SetMapSize(kMapWidth, kMapHeight);
    builder.SetMinRoomSize(kMinRoomSizeWidthNormal, kMinRoomSizeHeightNormal);
    builder.SetMaxRoomSize(kMaxRoomSizeWidthNormal, kMaxRoomSizeHeightNormal);
    builder.SetMaxRoomPlacementAttempts(kMaxRoomPlacementAttempts);
    builder.SetMaxRooms(kMaxRoomsNormal);
    builder.SetDefaultPathAlgorithm(kDefaultPathAlgorithmNormal);
    builder.SetDiagonalCorridors(kDiagonalCorridorsNormal);
    builder.SetMinUpstairs(kMinUpstairsAmountNormal);
    builder.SetMaxUpstairs(kMaxUpstairsAmountNormal);
    builder.SetMinDownstairs(kMinDownstairsAmountNormal);
    builder.SetMaxDownstairs(kMaxDownstairsAmountNormal);
    builder.SetDigSpaceAroundStairs(kDigAroundStairsNormal);
    builder.SetDigStairsOnlyInRooms(kDigStairsOnlyInRoomsNormal);
}

std::shared_ptr<libpmg::DungeonMap> DungeonFactory::GenerateDungeon(DungeonCategory const &category) {
    // Reset map
    category_builders_[category]->ResetMap(true);
    
    // Setup builder settings
    SetupBuilder(*category_builders_[category]);
    
    // Generate the features
    category_builders_[category]->GenerateRooms();
    category_builders_[category]->GenerateCorridors();
    category_builders_[category]->GenerateDoors();
    category_builders_[category]->GenerateWallStairs();
    category_builders_[category]->GenerateGroundStairs();

    // Generate dungeon
    std::shared_ptr<libpmg::Map> map_sp {std::move(category_builders_[category]->Build())};
    
    auto dungeon_sp {std::static_pointer_cast<libpmg::DungeonMap> (map_sp)};
    
    assert (dungeon_sp != nullptr);
    
    return dungeon_sp;
}
