#include "engine.hpp"
#include "game_constants.hpp"
#include "libpmg.hpp"
#include "monster.hpp"
#include "stats.hpp"

#include <iostream>

using namespace std;

libpmg::DungeonMap* InitDungeon() {
    // Initialize the dungeon builder
    auto dungeon_builder {libpmg::DungeonBuilder()};
    
    // Setup the map
    dungeon_builder.SetMapSize(kMapWidth, kMapHeight);
    dungeon_builder.SetMinRoomSize(4, 4);
    dungeon_builder.SetMaxRoomSize(12, 12);
    dungeon_builder.SetMaxRoomPlacementAttempts(10);
    dungeon_builder.SetMaxRooms(30);
    dungeon_builder.SetDefaultPathAlgorithm(libpmg::PathAlgorithm::ASTAR_BFS_MIX);
    dungeon_builder.SetDiagonalCorridors(false);
    
    // Initialize the map
    dungeon_builder.InitMap();
    
    // Generate the features
    dungeon_builder.GenerateRooms();
    dungeon_builder.GenerateCorridors();
    dungeon_builder.GenerateDoors();
    
    // DungeonMap
    return (libpmg::DungeonMap*) dungeon_builder.Build().release();
}

void SetupDungeonGame(Engine &eng, libpmg::DungeonMap *dungeon_map) {
    // Player generation
    auto start_coords {dungeon_map->GetRoomList()[0].GetRndCoords()};
    
    auto stats {Stats(5, 5, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10)};

    string name {"hero"};

    auto player {std::make_shared<Player>()};

    player->Initialize(start_coords.first,
                       start_coords.second,
                       '@',
                       name,
                       TCODColor::white,
                       stats,
                       eng.GetActionManager(),
                       eng.GetMapsManager());

    // Monster generation
    auto m_start_coords {dungeon_map->GetRoomList()[2].GetRndCoords()};
    
    auto m_stats {Stats(2, 2, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10)};

    string m_name {"goblin"};

    eng.InitializeGame(*dungeon_map, player);

    auto goblin {std::make_shared<Monster>()};
    goblin->Initialize(m_start_coords.first,
                       m_start_coords.second,
                       'g',
                       m_name,
                       TCODColor::green,
                       m_stats,
                       eng.GetActionManager(),
                       eng.GetMapsManager());

    // Add a monster to the dungeon
    eng.AddMonster(goblin);
}

int main(int argc, char **argv) {
    srand (time(NULL));
    
    // Initialize the random manager
    libpmg::RndManager::seed_ = rand();

    // DungeonMap
    auto dungeon_map {InitDungeon()};
    dungeon_map->Print();
    
    // Engine initialization
    Engine eng;
    
    SetupDungeonGame(eng, dungeon_map);
    
    // Game loop
    while ( !TCODConsole::isWindowClosed() ) {
        eng.RenderStartScreen();
        eng.UpdateStartScreen();

        while (eng.IsPlaying()) {
            eng.Render();
            eng.Update();
        }

    }

    return 0;
}
