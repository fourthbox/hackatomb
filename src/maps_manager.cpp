#include "maps_manager.hpp"
#include "game_constants.hpp"
#include "game_utils.hpp"
#include "libtcod.hpp"

#include <cassert>

typedef std::shared_ptr<Actor> Actor_p;

using std::string;

MapsManager::MapsManager()
    : initialized_ {false} {
    assert (!initialized_);
}

void MapsManager::AddMapToMaster(std::unique_ptr<Map> map, string map_category, short floor) {
    assert(floor >= -1);
    
    if (floor == -1) {
        master_maps_holder_[map_category][master_maps_holder_[map_category].size()] = std::move(map);
    } else {
        master_maps_holder_[map_category][floor] = std::move(map);
    }
}

bool MapsManager::CanMoveToPosition(size_t x, size_t y, string map_category, short floor) {
    assert(master_maps_holder_.count(map_category) > 0 && master_maps_holder_[map_category].count(floor) > 0);
    
    return master_maps_holder_[map_category][floor]->isWalkable(x, y);
}

void MapsManager::Draw(string map_category, short floor, std::shared_ptr<TCODConsole> console) {
    assert(initialized_ &&
           master_maps_holder_.count(map_category) > 0 && master_maps_holder_[map_category].count(floor) >0);
    
    // Draw the current map
    master_maps_holder_[map_category][floor]->Draw(console);

}

void MapsManager::ComputeFov(Player_p player, string map_category, short floor) {
    assert(master_maps_holder_.count(map_category) > 0 && master_maps_holder_[map_category].count(floor) >0);

    master_maps_holder_[map_category][floor]->computeFov(player->GetPosition().GetX(),
                                                         player->GetPosition().GetY(),
                                                         player->GetFovRadius());
}

void MapsManager::Initialize() {
    assert (!initialized_);
        
    initialized_ = true;
}

bool MapsManager::IsInFov(size_t x, size_t y, string map_category, short floor) {
    assert(master_maps_holder_.count(map_category) > 0 && master_maps_holder_[map_category].count(floor) >0);
    
    return master_maps_holder_[map_category][floor]->IsInFov(x, y);
}

