#include "dungeon_factory.hpp"

#include "game_constants.hpp"
#include "game_globals.hpp"

// Normal
static const size_t kMinRoomSizeWidthNormal =                         4;
static const size_t kMinRoomSizeHeightNormal =                        4;
static const size_t kMaxRoomSizeWidthNormal =                         12;
static const size_t kMaxRoomSizeHeightNormal =                        12;
static const size_t kMaxRoomsNormal =                                 30;
static const libpmg::PathAlgorithm kDefaultPathAlgorithmNormal =      libpmg::PathAlgorithm::ASTAR_BFS_MIX;
static const bool kDiagonalCorridorsNormal =                          false;

// Fire
static const size_t kMinRoomSizeWidthFire =                         4;
static const size_t kMinRoomSizeHeightFire =                        4;
static const size_t kMaxRoomSizeWidthFire =                         12;
static const size_t kMaxRoomSizeHeightFire =                        12;
static const size_t kMaxRoomsFire =                                 30;
static const libpmg::PathAlgorithm kDefaultPathAlgorithmFire =      libpmg::PathAlgorithm::ASTAR_BFS_MIX;
static const bool kDiagonalCorridorsFire =                          false;

// Ice
static const size_t kMinRoomSizeWidthIce =                         4;
static const size_t kMinRoomSizeHeightIce =                        4;
static const size_t kMaxRoomSizeWidthIce =                         12;
static const size_t kMaxRoomSizeHeightIce =                        12;
static const size_t kMaxRoomsIce =                                 30;
static const libpmg::PathAlgorithm kDefaultPathAlgorithmIce =      libpmg::PathAlgorithm::ASTAR_BFS_MIX;
static const bool kDiagonalCorridorsIce =                          false;

// Forest
static const size_t kMinRoomSizeWidthForest =                         4;
static const size_t kMinRoomSizeHeightForest =                        4;
static const size_t kMaxRoomSizeWidthForest =                         12;
static const size_t kMaxRoomSizeHeightForest =                        12;
static const size_t kMaxRoomsForest =                                 30;
static const libpmg::PathAlgorithm kDefaultPathAlgorithmForest =      libpmg::PathAlgorithm::ASTAR_BFS_MIX;
static const bool kDiagonalCorridorsForest =                          false;

// Undead
static const size_t kMinRoomSizeWidthUndead =                         4;
static const size_t kMinRoomSizeHeightUndead =                        4;
static const size_t kMaxRoomSizeWidthUndead =                         12;
static const size_t kMaxRoomSizeHeightUndead =                        12;
static const size_t kMaxRoomsUndead =                                 30;
static const libpmg::PathAlgorithm kDefaultPathAlgorithmUndead =      libpmg::PathAlgorithm::ASTAR_BFS_MIX;
static const bool kDiagonalCorridorsUndead =                          false;

DungeonFactory::DungeonFactory() {

    // Initialize the normal dungeon builder
    category_builders_[DungeonCategory::NORMAL_] = std::make_unique<libpmg::DungeonBuilder>();
    category_builders_[DungeonCategory::NORMAL_]->SetMapSize(kMapWidth, kMapHeight);
    category_builders_[DungeonCategory::NORMAL_]->SetMinRoomSize(kMinRoomSizeWidthNormal, kMinRoomSizeHeightNormal);
    category_builders_[DungeonCategory::NORMAL_]->SetMaxRoomSize(kMaxRoomSizeWidthNormal, kMaxRoomSizeHeightNormal);
    category_builders_[DungeonCategory::NORMAL_]->SetMaxRoomPlacementAttempts(kMaxRoomPlacementAttempts);
    category_builders_[DungeonCategory::NORMAL_]->SetMaxRooms(kMaxRoomsNormal);
    category_builders_[DungeonCategory::NORMAL_]->SetDefaultPathAlgorithm(kDefaultPathAlgorithmNormal);
    category_builders_[DungeonCategory::NORMAL_]->SetDiagonalCorridors(kDiagonalCorridorsNormal);
    
    // Initialize the fire dungeon builder
    auto fire_dungeon_builder {std::make_unique<libpmg::DungeonBuilder>()};
    fire_dungeon_builder->SetMapSize(kMapWidth, kMapHeight);
    fire_dungeon_builder->SetMinRoomSize(kMinRoomSizeWidthFire, kMinRoomSizeHeightFire);
    fire_dungeon_builder->SetMaxRoomSize(kMaxRoomSizeWidthFire, kMaxRoomSizeHeightFire);
    fire_dungeon_builder->SetMaxRoomPlacementAttempts(kMaxRoomPlacementAttempts);
    fire_dungeon_builder->SetMaxRooms(kMaxRoomsFire);
    fire_dungeon_builder->SetDefaultPathAlgorithm(kDefaultPathAlgorithmFire);
    fire_dungeon_builder->SetDiagonalCorridors(kDiagonalCorridorsFire);

    category_builders_[DungeonCategory::FIRE_] = std::move(fire_dungeon_builder);

    // Initialize the ice dungeon builder
    auto ice_dungeon_builder {std::make_unique<libpmg::DungeonBuilder>()};
    ice_dungeon_builder->SetMapSize(kMapWidth, kMapHeight);
    ice_dungeon_builder->SetMinRoomSize(kMinRoomSizeWidthIce, kMinRoomSizeHeightIce);
    ice_dungeon_builder->SetMaxRoomSize(kMaxRoomSizeWidthIce, kMaxRoomSizeHeightIce);
    ice_dungeon_builder->SetMaxRoomPlacementAttempts(kMaxRoomPlacementAttempts);
    ice_dungeon_builder->SetMaxRooms(kMaxRoomsIce);
    ice_dungeon_builder->SetDefaultPathAlgorithm(kDefaultPathAlgorithmIce);
    ice_dungeon_builder->SetDiagonalCorridors(kDiagonalCorridorsIce);

    category_builders_[DungeonCategory::ICE_] = std::move(ice_dungeon_builder);

    // Initialize the forest dungeon builder
    auto forest_dungeon_builder {std::make_unique<libpmg::DungeonBuilder>()};
    forest_dungeon_builder->SetMapSize(kMapWidth, kMapHeight);
    forest_dungeon_builder->SetMinRoomSize(kMinRoomSizeWidthForest, kMinRoomSizeHeightForest);
    forest_dungeon_builder->SetMaxRoomSize(kMaxRoomSizeWidthForest, kMaxRoomSizeHeightForest);
    forest_dungeon_builder->SetMaxRoomPlacementAttempts(kMaxRoomPlacementAttempts);
    forest_dungeon_builder->SetMaxRooms(kMaxRoomsForest);
    forest_dungeon_builder->SetDefaultPathAlgorithm(kDefaultPathAlgorithmForest);
    forest_dungeon_builder->SetDiagonalCorridors(kDiagonalCorridorsForest);

    category_builders_[DungeonCategory::FOREST_] = std::move(forest_dungeon_builder);

    // Initialize the undead dungeon builder
    auto undead_dungeon_builder {std::make_unique<libpmg::DungeonBuilder>()};
    undead_dungeon_builder->SetMapSize(kMapWidth, kMapHeight);
    undead_dungeon_builder->SetMinRoomSize(kMinRoomSizeWidthUndead, kMinRoomSizeHeightUndead);
    undead_dungeon_builder->SetMaxRoomSize(kMaxRoomSizeWidthUndead, kMaxRoomSizeHeightUndead);
    undead_dungeon_builder->SetMaxRoomPlacementAttempts(kMaxRoomPlacementAttempts);
    undead_dungeon_builder->SetMaxRooms(kMaxRoomsUndead);
    undead_dungeon_builder->SetDefaultPathAlgorithm(kDefaultPathAlgorithmUndead);
    undead_dungeon_builder->SetDiagonalCorridors(kDiagonalCorridorsUndead);

    category_builders_[DungeonCategory::UNDEAD_] = std::move(undead_dungeon_builder);
}

std::shared_ptr<libpmg::DungeonMap> DungeonFactory::GenerateDungeon(DungeonCategory const &category) {
    category_builders_[category]->ResetMap(true);
    
    // Generate the features
    category_builders_[category]->GenerateRooms();
    category_builders_[category]->GenerateCorridors();
    category_builders_[category]->GenerateDoors();

    // Generate dungeon
    auto dungeon {std::static_pointer_cast<libpmg::DungeonMap> (category_builders_[category]->Build())};
    
    assert (dungeon != nullptr);
    
    return dungeon;
}
