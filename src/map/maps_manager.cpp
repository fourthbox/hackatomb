#include "maps_manager.hpp"

#include "door_tile.hpp"
#include "engine.hpp"
#include "game_constants.hpp"
#include "game_utils.hpp"
#include "libtcod.hpp"
#include "player.hpp"

void MapsManager::AddMapToMaster(std::unique_ptr<Map> map, DungeonCategory map_category, int floor) {
    assert(floor >= -1);
    
    // If -1, set to the last floor
    if (floor == -1)
        floor = master_maps_holder_[map_category].size();
    
    // Insert map in maps holder
    master_maps_holder_[map_category][floor] = std::move(map);
}

bool MapsManager::IsTileWalkable(MapLocation const &location) {
    assert(master_maps_holder_.count(location.dungeon_category_) > 0 &&
           master_maps_holder_[location.dungeon_category_].count(location.floor_) > 0);
    
    return master_maps_holder_
        [location.dungeon_category_]
        [location.floor_]
        ->isWalkable(location.x_, location.y_);
}

void MapsManager::Draw(TCODConsole &console, Actor const &actor) {
    assert(initialized_ &&
           master_maps_holder_.count(actor.GetMapLocation().dungeon_category_) > 0 &&
           master_maps_holder_[actor.GetMapLocation().dungeon_category_].count(actor.GetMapLocation().floor_) > 0);
    
    // Recompute fov for hero
    ComputeFov(actor);
    
    // Refresh the console if needed
    if (need_refresh_) {
        console.clear();
        need_refresh_ = false;
    }
    
    // Draw the current map
    master_maps_holder_[actor.GetMapLocation().dungeon_category_][actor.GetMapLocation().floor_]->Draw(console);
}

void MapsManager::ComputeFov(Actor const &actor) {
    
    assert(master_maps_holder_.count(actor.GetMapLocation().dungeon_category_) > 0);
    assert(master_maps_holder_[actor.GetMapLocation().dungeon_category_].count(actor.GetMapLocation().floor_) > 0);

    master_maps_holder_
        [actor.GetMapLocation().dungeon_category_]
        [actor.GetMapLocation().floor_]
        ->computeFov(actor.GetPosition().first,
                     actor.GetPosition().second,
                     actor.GetFovRadius());
}

void MapsManager::Initialize() {
    assert (!initialized_);
    
    // Initialize first dungeon map
    for (auto i {0}; i < kMinFloorsLoaded; i++)
        LoadDungeonFloor(DungeonCategory::NORMAL_, i);
    
    initialized_ = true;
}

void MapsManager::LoadDungeonFloor(DungeonCategory category, int floor) {
    assert(floor >= 0);
    assert(floor <= kStandardDungeonDepth);
    
    // Generate dungeon floor
    auto map_p {std::make_unique<Map>(*dungeon_factory_.BuildDungeon(category, floor), category)};
    
    // Add to map master
    AddMapToMaster(std::move(map_p), category, floor);
}

bool MapsManager::IsInFov(Actor const &actor, MapLocation const &map_location) {
    assert(initialized_);
    
    ComputeFov(actor);

    assert(master_maps_holder_.count(map_location.dungeon_category_) > 0);
    assert(master_maps_holder_[map_location.dungeon_category_].count(map_location.floor_) > 0);
    
    // If the location is on another floor, return false
    if (actor.GetMapLocation().floor_ != map_location.floor_)
        return false;
    
    return master_maps_holder_
        [map_location.dungeon_category_]
        [map_location.floor_]
        ->IsInFov(map_location.x_, map_location.y_);
}

bool MapsManager::IsInteractable(MapLocation const &location) {
    assert(initialized_);
    
    assert(master_maps_holder_.count(location.dungeon_category_) > 0);
    assert(master_maps_holder_[location.dungeon_category_].count(location.floor_) > 0);

    return master_maps_holder_[location.dungeon_category_][location.floor_]->HasDoor(location.x_, location.y_);
}

void MapsManager::OpenDoor(MapLocation const &location) {
    assert(initialized_);
    
    assert(master_maps_holder_.count(location.dungeon_category_) > 0);
    assert(master_maps_holder_[location.dungeon_category_].count(location.floor_) > 0);
    
    auto door {static_cast<DoorTile*> (master_maps_holder_
                                       [location.dungeon_category_]
                                       [location.floor_]
                                       ->GetTile(location.x_, location.y_))};
    
    assert (door != nullptr);
    
    door->Open();
    
    master_maps_holder_
        [location.dungeon_category_]
        [location.floor_]
        ->UpdateTcodProperties(door);
}

std::unique_ptr<TCODPath> MapsManager::AllocatePathFromFloor(DungeonCategory const &category, std::size_t const &floor, ITCODPathCallback const *callback, float diagonal_cost) {
    assert(initialized_);
    
    return std::make_unique<TCODPath>(master_maps_holder_[category][floor]->getWidth(),
                                      master_maps_holder_[category][floor]->getHeight(),
                                      callback,
                                      master_maps_holder_[category][floor].get(),
                                      diagonal_cost);
}

void MapsManager::SetAllExplored(DungeonCategory const &category, std::size_t const &floor) {
    assert(initialized_);

    master_maps_holder_[category][floor]->SetAllExplored();
}

MapLocation MapsManager::GetRandomLocation(DungeonCategory const &category, std::size_t const &floor, int room_number) {
    assert(initialized_);
    assert(master_maps_holder_.count(category) > 0);
    assert(master_maps_holder_[category].count(floor) > 0);

    if (room_number == -1)
        room_number = Engine::GetRandomUintFromRange(0, master_maps_holder_[category][floor]->GetRoomList().size()-1);
    
    auto rnd_coors {master_maps_holder_[category][floor]->GetRoomList()[room_number]->GetRndCoords()};
    
    return MapLocation(category, floor, rnd_coors.first, rnd_coors.second);
}

Tile *MapsManager::GetTileFromFloor(MapLocation const &location) {
    assert(initialized_);
    assert(master_maps_holder_.count(location.dungeon_category_) > 0);
    assert(master_maps_holder_[location.dungeon_category_].count(location.floor_) > 0);
    
    return master_maps_holder_
        [location.dungeon_category_]
        [location.floor_]
        ->GetTile(location.x_, location.y_);
}

MapLocation_opt MapsManager::MoveToFloor(MapLocation const &current_location, bool is_upstairs) {
    assert(initialized_);
    
    MapLocation new_location (current_location.dungeon_category_,
                              (is_upstairs ? current_location.floor_-1 : current_location.floor_+1),
                              current_location.x_,
                              current_location.y_);
    
    assert(new_location.floor_ >= 0);
    assert(new_location.floor_ <= kStandardDungeonDepth);
    assert(master_maps_holder_.count(new_location.dungeon_category_) > 0);
    

    // If the new floor has not already been loaded, create it
    if (master_maps_holder_[new_location.dungeon_category_].count(new_location.floor_) == 0) {
        
        // TODO: actually make the load procedure async
        // Aync load new floor
        LoadDungeonFloor(new_location.dungeon_category_, new_location.floor_);
        
        assert(master_maps_holder_[new_location.dungeon_category_].count(new_location.floor_) > 0);
    }
        
    // Refresh the console on the next draw itetation
    need_refresh_ = true;
    
    // Return start position on the floor
    return (is_upstairs ? GetExitPosition(new_location) : GetEntrancePosition(new_location));
}

MapLocation_opt MapsManager::GetEntrancePosition(MapLocation const &location) {
    assert(initialized_);
    assert(master_maps_holder_.count(location.dungeon_category_) > 0);
    assert(master_maps_holder_[location.dungeon_category_].count(location.floor_) > 0);
    
    auto tile {master_maps_holder_[location.dungeon_category_][location.floor_]->GetEntranceTile()};
    
    if (tile == nullptr)
        return std::experimental::nullopt;
    
    // Create new location
    MapLocation new_location (location.dungeon_category_, location.floor_, tile->GetX(), tile->GetY());
    
    return std::experimental::make_optional(new_location);
}

MapLocation_opt MapsManager::GetExitPosition(MapLocation const &location) {
    assert(initialized_);
    assert(master_maps_holder_.count(location.dungeon_category_) > 0);
    assert(master_maps_holder_[location.dungeon_category_].count(location.floor_) > 0);

    auto tile {master_maps_holder_[location.dungeon_category_][location.floor_]->GetExitTile()};
    
    if (tile == nullptr)
        return std::experimental::nullopt;
    
    // Create new location
    MapLocation new_location (location.dungeon_category_, location.floor_, tile->GetX(), tile->GetY());
    
    return std::experimental::make_optional(new_location);
}

std::map<size_t, std::unique_ptr<Map>> *MapsManager::GetDungeonByCategory(DungeonCategory category) {
    assert(initialized_);
    assert(master_maps_holder_.count(category) > 0);

    return &master_maps_holder_[category];
}

bool MapsManager::IsFloorLoaded(MapLocation const &location) {
    assert(initialized_);
    assert(master_maps_holder_.count(location.dungeon_category_) > 0);

    return master_maps_holder_[location.dungeon_category_].count(location.floor_) == 1;
}
