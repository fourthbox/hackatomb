//#include "engine.hpp"
//
//int main(int argc, char **argv) {
//    srand (time(NULL));
//
//    // Initialize the random manager
//    libpmg::RndManager::seed_ = rand();
//
//    // Engine initialization
//    Engine eng;
//    eng.InitializeStartScreen();
//
//    // Game loop
//    while ( !TCODConsole::isWindowClosed() ) {
//        eng.RenderStartScreen();
//        eng.UpdateStartScreen();
//
//        while (eng.IsPlaying()) {
//            eng.Render();
//            eng.Update();
//        }
//
//    }
//
//    return 0;
//}


#include "libpmg.hpp"

using namespace libpmg;

int main(int argc, char **argv) {
    srand (time(NULL));

    // Initialize the random manager
    libpmg::RndManager::seed_ = std::rand();
    
    // Initialize the builder
    DungeonBuilder builder;
    
    // Setup the map
    builder.SetMapSize(100, 45);
    builder.SetMinRoomSize(4, 4);
    builder.SetMaxRoomSize(12, 12);
    builder.SetMaxRoomPlacementAttempts(10);
    builder.SetMaxRooms(10);
    builder.SetDefaultPathAlgorithm(PathAlgorithm::ASTAR_BFS_MIX);
    builder.SetDiagonalCorridors(true);
    
    // Initialize the map
    builder.InitMap();
    
    // Generate the features
    builder.GenerateRooms();
    builder.GenerateCorridors();
    builder.GenerateDoors();
//    builder.GenerateWallStairs(1, 1);
    builder.GenerateGroundStairs(5, 5, true, false);
    
    // Build the map
    std::shared_ptr<Map> map {builder.Build()};
    
    // Print a sample
    map->Print();
    
    return 0;
}
