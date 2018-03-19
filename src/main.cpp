#include "engine.hpp"
#include "game_constants.hpp"
#include "key_mapper.hpp"
#include "libpmg.hpp"
#include "monster.hpp"

using namespace std;

std::shared_ptr<libpmg::DungeonMap> InitDungeon() {
    // Initialize the dungeon builder
    auto dungeon_builder {std::make_shared<libpmg::DungeonBuilder>()};
    
    // Setup the map
    dungeon_builder->SetMapSize(kMapWidth, kMapHeight);
    dungeon_builder->SetMinRoomSize(4, 4);
    dungeon_builder->SetMaxRoomSize(12, 12);
    dungeon_builder->SetMaxRoomPlacementAttempts(10);
    dungeon_builder->SetMaxRooms(20);
    dungeon_builder->SetDefaultPathAlgorithm(libpmg::PathAlgorithm::ASTAR_BFS_MIX);
    dungeon_builder->SetDiagonalCorridors(false);
    
    // Initialize the map
    dungeon_builder->InitMap();
    
    // Generate the features
    dungeon_builder->GenerateRooms();
    dungeon_builder->GenerateCorridors();
    dungeon_builder->GenerateDoors();
    
    // DungeonMap
    return std::static_pointer_cast<libpmg::DungeonMap>(dungeon_builder->Build());
}

void SetupDungeonGame(Engine &eng, std::shared_ptr<libpmg::DungeonMap> dungeon_map) {
    // Player generation
    auto start_coords {dungeon_map->GetRoomList()[0].GetRndCoords()};
    
    auto stats {Stats(5, 5, 10)};

    string name {"hero"};

    auto player {std::make_shared<Player>()};

    player->Initialize(start_coords.first,
                       start_coords.second,
                       '@',
                       name,
                       TCODColor::white,
                       stats,
                       eng.GetActionManager());

    // Monster generation
    auto m_start_coords {dungeon_map->GetRoomList()[2].GetRndCoords()};
    
    auto m_stats {Stats(2, 2, 10)};

    string m_name {"goblin"};

    auto goblin {std::make_shared<Monster>()};
    goblin->Initialize(m_start_coords.first,
                       m_start_coords.second,
                       'g',
                       m_name,
                       TCODColor::green,
                       m_stats,
                       eng.GetActionManager());

    eng.Initialize(dungeon_map,
                   player);

    // Add a monster to the dungeon
    eng.AddMonster(goblin);
}

std::shared_ptr<libpmg::WorldMap> InitWorld() {
    // Initialize the dungeon builder
    auto world_builder {std::make_shared<libpmg::WorldBuilder>()};

    // Setup the map
    world_builder->SetMapSize(kRootViewWidth, kRootViewHeight);
    world_builder->SetNoiseType(FastNoise::PerlinFractal);
    world_builder->SetNoiseFrequency(0.05f);
    world_builder->SetFractalLacunarity(2.9f);
    world_builder->SetFractalGain(0.35f);
    world_builder->SetFractalOctaves(10);
    world_builder->SetExtremeMultiplier(2.0f);
    world_builder->SetSeaLevelMultiplier(2.0f);
    world_builder->SetPoleElevationMultiplier(20.0f);

    // Initialize the map
    world_builder->InitMap();

    // Generate the features
    world_builder->GenerateHeightMap();
    world_builder->ApplyHeightMap();
    
    // DungeonMap
    return std::static_pointer_cast<libpmg::WorldMap>(world_builder->Build());
}

void SetupWorldGame(Engine &eng, std::shared_ptr<libpmg::WorldMap> world_map) {
    eng.Initialize(world_map);
}

int main(int argc, char **argv) {

    srand (time(NULL));
    
    // Initialize the random manager
    libpmg::RndManager::seed_ = rand();

    // DungeonMap
    auto dungeon_map {InitDungeon()};
    dungeon_map->Print();
    
    // Initialize the world builder
//    auto world_map {InitWorld()};
    
    // Engine initialization
    auto eng = Engine();
    
    SetupDungeonGame(eng, dungeon_map);
//    SetupWorldGame(eng, world_map);
        
    // Game loop
    while ( !TCODConsole::isWindowClosed() ) {

        eng.Update();
        eng.Render();
        
//        eng.RenderWorld();
        
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS|TCOD_EVENT_MOUSE,
                                  &KeyMapper::LastKey,
                                  &KeyMapper::LastMousePosition);
    }

    return 0;
}
