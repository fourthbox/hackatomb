#include "maps_manager.hpp"

#include "game_constants.hpp"
#include "game_utils.hpp"
#include "libtcod.hpp"
#include "player.hpp"

using std::string;

void MapsManager::AddMapToMaster(Map_p map, string &map_category, short floor) {
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

void MapsManager::Draw(std::shared_ptr<TCODConsole> console) {
    assert(initialized_ &&
           master_maps_holder_.count(current_map_category_) > 0 &&
           master_maps_holder_[current_map_category_].count(current_floor_) > 0);
    
    // Draw the current map
    master_maps_holder_[current_map_category_][current_floor_]->Draw(console);

}

void MapsManager::ComputeFov(Player_p player) {
    assert(master_maps_holder_.count(current_map_category_) > 0 &&
           master_maps_holder_[current_map_category_].count(current_floor_) > 0);

    master_maps_holder_[current_map_category_][current_floor_]->computeFov(player->GetPosition().first,
                                                                           player->GetPosition().second,
                                                                           player->GetFovRadius());
}

void MapsManager::Initialize() {
    assert (!initialized_);
        
    initialized_ = true;
}

bool MapsManager::IsInFov(size_t x, size_t y) {
    assert(master_maps_holder_.count(current_map_category_) > 0 &&
           master_maps_holder_[current_map_category_].count(current_floor_) > 0);
    
    return master_maps_holder_[current_map_category_][current_floor_]->IsInFov(x, y);
}
