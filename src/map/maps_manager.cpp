#include "maps_manager.hpp"

#include "door_tile.hpp"
#include "engine.hpp"
#include "game_constants.hpp"
#include "game_utils.hpp"
#include "libtcod.hpp"
#include "player.hpp"

void MapsManager::AddMapToMaster(std::unique_ptr<Map> map, DungeonCategory map_category, short floor) {
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

void MapsManager::Draw(TCODConsole &console, Actor const &actor) {
    assert(initialized_ &&
           master_maps_holder_.count(current_map_category_) > 0 &&
           master_maps_holder_[current_map_category_].count(current_floor_) > 0);
    
    // Recompute fov for hero
    ComputeFov(actor);
    
    // Refresh the console if needed
    if (need_refresh_) {
        console.clear();
        need_refresh_ = false;
    }
    
    // Draw the current map
    master_maps_holder_[current_map_category_][current_floor_]->Draw(console);
}

void MapsManager::ComputeFov(Actor const &actor) {
    assert(master_maps_holder_.count(current_map_category_) > 0 &&
           master_maps_holder_[current_map_category_].count(current_floor_) > 0);

    master_maps_holder_[current_map_category_][current_floor_]->computeFov(actor.GetPosition().first,
                                                                           actor.GetPosition().second,
                                                                           actor.GetFovRadius());
}

void MapsManager::Initialize() {
    assert (!initialized_);
    
    // Initialize first dungeon map
    LoadDungeonFloor(DungeonCategory::NORMAL_, 0);
    
    initialized_ = true;
}

void MapsManager::LoadDungeonFloor(DungeonCategory category, short floor) {
    assert(floor >= 0 && floor <= kStandardDungeonDepth);
    
    // Generate dungeon floor
    auto map_p {std::make_unique<Map>(*dungeon_factory_.GenerateDungeon(category, floor))};
    
    // Add to map master
    AddMapToMaster(std::move(map_p), category, floor);
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
        room_number = Engine::GetRandomUintFromRange(0, master_maps_holder_[current_map_category_][current_floor_]->GetRoomList().size()-1);

    return master_maps_holder_[current_map_category_][current_floor_]->GetRoomList()[room_number]->GetRndCoords();
}

Tile *MapsManager::GetTileFromFloor(size_t x, size_t y, short floor) {
    assert(initialized_);
    
    if (floor == -1)
        floor = current_floor_;
    
    assert(master_maps_holder_.count(current_map_category_) > 0 &&
           master_maps_holder_[current_map_category_].count(floor) > 0);

    
    return master_maps_holder_[current_map_category_][floor]->GetTile(x, y);
}

CoordinateOpt MapsManager::MoveToFloor(bool is_upstairs) {
    assert(initialized_);
    
    if (is_upstairs)
        current_floor_ --;
    else
        current_floor_ ++;
    
    assert(current_floor_ >= 0
           && current_floor_ <= kStandardDungeonDepth
           && master_maps_holder_.count(current_map_category_) > 0);
    
    // If the new floor has not already been explored, create it
    if (master_maps_holder_[current_map_category_].count(current_floor_) == 0) {
        // Aync load new floor
        LoadDungeonFloor(current_map_category_, current_floor_);
        
        assert(master_maps_holder_[current_map_category_].count(current_floor_) > 0);
    }
    
    // Refresh the console on the next draw itetation
    need_refresh_ = true;
    
    // Return start position on the floor
    return (is_upstairs ? GetExitPosition() : GetEntrancePosition());
}

CoordinateOpt MapsManager::GetEntrancePosition() {
    assert(initialized_);
    
    assert(master_maps_holder_.count(current_map_category_) > 0 &&
           master_maps_holder_[current_map_category_].count(current_floor_) > 0);
    
    auto tile {master_maps_holder_[current_map_category_][current_floor_]->GetEntranceTile()};
    
    if (tile == nullptr)
        return std::experimental::nullopt;

    return std::experimental::make_optional(tile->GetXY());
}

CoordinateOpt MapsManager::GetExitPosition() {
    assert(initialized_);
    
    assert(master_maps_holder_.count(current_map_category_) > 0 &&
           master_maps_holder_[current_map_category_].count(current_floor_) > 0);

    auto tile {master_maps_holder_[current_map_category_][current_floor_]->GetExitTile()};
    
    if (tile == nullptr)
        return std::experimental::nullopt;
    
    return std::experimental::make_optional(tile->GetXY());
}

