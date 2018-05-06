#include "maps_manager.hpp"

#include "door_tile.hpp"
#include "game_constants.hpp"
#include "game_utils.hpp"
#include "libtcod.hpp"
#include "player.hpp"

using std::string;

void MapsManager::AddMapToMaster(std::unique_ptr<Map> map, string map_category, short floor) {
    assert(floor >= -1);
    
    // Set current floor and categoty
    current_map_category_ = map_category;
    // Insert map in maps holder
    if (floor == -1) {
        current_floor_ = master_maps_holder_[map_category].size();
        master_maps_holder_[map_category][current_floor_] = std::move(map);
    } else {
        current_floor_ = floor;
        master_maps_holder_[map_category][floor] = std::move(map);
    }
}

bool MapsManager::CanMoveToPosition(size_t x, size_t y) {
    assert(master_maps_holder_.count(current_map_category_) > 0 &&
           master_maps_holder_[current_map_category_].count(current_floor_) > 0);
    
    return master_maps_holder_[current_map_category_][current_floor_]->isWalkable(x, y);
}

void MapsManager::Draw(TCODConsole *console, Actor *actor) {
    assert(initialized_ &&
           master_maps_holder_.count(current_map_category_) > 0 &&
           master_maps_holder_[current_map_category_].count(current_floor_) > 0);
    
    // Recompute fov for hero
    ComputeFov(actor);
    
    // Draw the current map
    master_maps_holder_[current_map_category_][current_floor_]->Draw(console);

}

void MapsManager::ComputeFov(Actor *actor) {
    assert(master_maps_holder_.count(current_map_category_) > 0 &&
           master_maps_holder_[current_map_category_].count(current_floor_) > 0);

    master_maps_holder_[current_map_category_][current_floor_]->computeFov(actor->GetPosition().first,
                                                                           actor->GetPosition().second,
                                                                           actor->GetFovRadius());
}

void MapsManager::Initialize() {
    assert (!initialized_);
    
    // TODO: initialize all floor
    
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

    // Generate
    libpmg::DungeonMap* map {(libpmg::DungeonMap*) dungeon_builder.Build().release()};
    
    auto map_p {std::make_unique<Map>(*map)};
        
    AddMapToMaster(std::move(map_p), "standard_dungeon");
    
    initialized_ = true;
}

bool MapsManager::IsInFov(size_t x, size_t y) {
    assert(initialized_);

    assert(master_maps_holder_.count(current_map_category_) > 0 &&
           master_maps_holder_[current_map_category_].count(current_floor_) > 0);
    
    return master_maps_holder_[current_map_category_][current_floor_]->IsInFov(x, y);
}

bool MapsManager::IsInteractable(size_t x, size_t y) {
    assert(initialized_);
    
    assert(master_maps_holder_.count(current_map_category_) > 0 &&
           master_maps_holder_[current_map_category_].count(current_floor_) > 0);

    return master_maps_holder_[current_map_category_][current_floor_]->HasDoor(x, y);
}

void MapsManager::OpenDoor(size_t x, size_t y) {
    assert(initialized_);
    
    assert(master_maps_holder_.count(current_map_category_) > 0 &&
           master_maps_holder_[current_map_category_].count(current_floor_) > 0);
    
    auto door {static_cast<DoorTile*> (master_maps_holder_[current_map_category_][current_floor_]->GetTile(x, y))};
    
    assert (door != nullptr);
    
    door->Open();
    master_maps_holder_[current_map_category_][current_floor_]->UpdateTcodProperties(door);
}

std::unique_ptr<TCODPath> MapsManager::AllocatePathFromCurrentFloor(ITCODPathCallback const *callback, float diagonal_cost) {
    assert(initialized_);
    
    return std::make_unique<TCODPath>(master_maps_holder_[current_map_category_][current_floor_]->getWidth(),
                                      master_maps_holder_[current_map_category_][current_floor_]->getHeight(),
                                      callback,
                                      master_maps_holder_[current_map_category_][current_floor_].get(),
                                      diagonal_cost);
}

void MapsManager::SetAllExplored() {
    assert(initialized_);

    master_maps_holder_[current_map_category_][current_floor_]->SetAllExplored();
}

std::pair<size_t, size_t> MapsManager::GetRandomPosition(int room_number) {
    assert(initialized_ && room_number < (int)master_maps_holder_[current_map_category_][current_floor_]->GetRoomList().size());

    if (room_number == -1)
        room_number = libpmg::RndManager::GetInstance().GetRandomUintFromRange(0, master_maps_holder_[current_map_category_][current_floor_]->GetRoomList().size()-1);

    return master_maps_holder_[current_map_category_][current_floor_]->GetRoomList()[room_number].GetRndCoords();
}
