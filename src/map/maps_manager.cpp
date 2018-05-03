#include "maps_manager.hpp"

#include "door_tile.hpp"
#include "game_constants.hpp"
#include "game_utils.hpp"
#include "libtcod.hpp"
#include "player.hpp"

using std::string;

void MapsManager::AddMapToMaster(std::unique_ptr<Map> map, string &map_category, short floor) {
    assert(floor >= -1);
    
    if (floor == -1) {
        master_maps_holder_[map_category][master_maps_holder_[map_category].size()] = std::move(map);
    } else {
        master_maps_holder_[map_category][floor] = std::move(map);
    }
}

bool MapsManager::CanMoveToPosition(size_t x, size_t y) {
    assert(master_maps_holder_.count(current_map_category_) > 0 &&
           master_maps_holder_[current_map_category_].count(current_floor_) > 0);
    
    return master_maps_holder_[current_map_category_][current_floor_]->isWalkable(x, y);
}

void MapsManager::Draw(std::shared_ptr<TCODConsole> console, std::shared_ptr<Actor> actor) {
    assert(initialized_ &&
           master_maps_holder_.count(current_map_category_) > 0 &&
           master_maps_holder_[current_map_category_].count(current_floor_) > 0);
    
    // Recompute fov for hero
    ComputeFov(actor);
    
    // Draw the current map
    master_maps_holder_[current_map_category_][current_floor_]->Draw(console);

}

void MapsManager::ComputeFov(Actor_p actor) {
    assert(master_maps_holder_.count(current_map_category_) > 0 &&
           master_maps_holder_[current_map_category_].count(current_floor_) > 0);

    master_maps_holder_[current_map_category_][current_floor_]->computeFov(actor->GetPosition().first,
                                                                           actor->GetPosition().second,
                                                                           actor->GetFovRadius());
}

void MapsManager::Initialize() {
    assert (!initialized_);
        
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
    
    auto door {std::static_pointer_cast<DoorTile> (master_maps_holder_[current_map_category_][current_floor_]->GetTile(x, y))};
    
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
    master_maps_holder_[current_map_category_][current_floor_]->SetAllExplored();
}
