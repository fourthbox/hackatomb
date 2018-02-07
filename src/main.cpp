#include "engine.hpp"
#include "game_constants.hpp"
#include "libpmg.hpp"

int main(int argc, char **argv) {

    srand (time(NULL));
    
    // Initialize the random manager
    libpmg::RndManager::seed = rand();

    // Initialize the builder
    auto builder {std::make_shared<libpmg::DungeonBuilder>()};
    
    // Setup the map
    builder->SetMapSize(kMapWidth, kMapHeight);
    builder->SetMinRoomSize(4, 4);
    builder->SetMaxRoomSize(12, 12);
    builder->SetMaxRoomPlacementAttempts(10);
    builder->SetMaxRooms(20);
    builder->SetDefaultPathAlgorithm(libpmg::PathAlgorithm::ASTAR_BFS_MIX);
    builder->SetDiagonalCorridors(false);
    
    // Initialize the map
    builder->InitMap();
    
    // Generate the features
    builder->GenerateRooms();
    builder->GenerateCorridors();
    builder->GenerateDoors();
    
    // Build the map
    auto map {builder->Build()};
    
    map->Print();
    
    // DungeonMap
    auto dungeon_map {std::static_pointer_cast<libpmg::DungeonMap>(map)};
    
    // Player generation
    auto start_coords {dungeon_map->room_list[0].GetRndCoords()};
    
    auto stats {Stats(5, 5, 10)};
    
    string name {"hero"};
    
    auto player {std::make_shared<Player>(Player(start_coords.first,
                                                 start_coords.second,
                                                 '@',
                                                 name,
                                                 TCODColor::white,
                                                 stats))};
    
    player->InitializeAi(std::make_shared<PlayerAi>());
    
    // Monster generation
    auto m_start_coords {dungeon_map->room_list[2].GetRndCoords()};
    
    auto m_stats {Stats(2, 2, 10)};
    
    string m_name {"goblin"};
    
    auto goblin {std::make_shared<Player>(Player(m_start_coords.first,
                                                 m_start_coords.second,
                                                 'g',
                                                 m_name,
                                                 TCODColor::green,
                                                 m_stats))};
    
    goblin->InitializeAi(std::make_shared<MonsterAi>());
    
    Engine& eng {Engine::GetInstance()};
    
    eng.Initialize(dungeon_map,
                   player);

    eng.AddMonster(goblin);
    
    while ( !TCODConsole::isWindowClosed() ) {
        eng.Update();
        eng.Render();
    }

    return 0;
}

