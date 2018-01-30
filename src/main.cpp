#include "engine.hpp"
#include "game_constants.hpp"
#include "libpmg.hpp"

int main(int argc, char **argv) {

    srand (time(NULL));
    
    // Initialize the random manager
    libpmg::RndManager::seed = rand();

    // Initialize the builder
    auto map {libpmg::MapBuilder()
        
        // Setup the map
        .SetMapSize(kMapWidth, kMapHeight)
        .SetMinRoomSize(4, 4)
        .SetMaxRoomSize(12, 12)
        .SetMaxRoomPlacementAttempts(10)
        .SetMaxRooms(20)
        .SetDefaultPathAlgorithm(libpmg::PathAlgorithm::ASTAR_BFS_MIX)
        .SetDiagonalCorridors(false)
        
        // Initialize the map
        .InitMap()
        
        // Generate the features
        .GenerateRooms()
        .GenerateCorridors()
        .GenerateDoors()
        
        // Build the map
        .Build()};
    
    map->Print();
    
    // Player generation
    auto start_coords {map->room_list[0].GetRndCoords()};
    
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
    auto m_start_coords {map->room_list[2].GetRndCoords()};
    
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
    
    eng.Initialize(map,
                   player);

    eng.AddMonster(goblin);
    
    while ( !TCODConsole::isWindowClosed() ) {
        eng.Update();
        eng.Render();
    }

    return 0;
}

