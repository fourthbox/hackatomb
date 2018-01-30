#include "maps_manager.hpp"
#include "game_utils.hpp"
#include "libtcod.hpp"

#include <cassert>

typedef std::shared_ptr<Actor> Actor_p;

using std::string;

// If floor is -1, it will assign the map with the lowest floor, and append it to the map
void MapsManager::AddMapToMaster(Map *map, string map_category, short floor) {
    assert(floor >= -1);
    
    if (floor == -1) {
        master_maps_holder_[map_category][master_maps_holder_[map_category].size()] = map;
    } else {
        master_maps_holder_[map_category][floor] = map;
    }
}

bool MapsManager::CanMoveToPosition(size_t x, size_t y, string map_category, short floor) {
    assert(master_maps_holder_.count(map_category) > 0 && master_maps_holder_[map_category].count(floor) > 0);
    
    return master_maps_holder_[map_category][floor]->isWalkable(x, y);
}

void MapsManager::Draw(string map_category, short floor) {
    assert(master_maps_holder_.count(map_category) > 0 && master_maps_holder_[map_category].count(floor) >0);
    
    master_maps_holder_[map_category][floor]->Draw();
}

MapsManager::~MapsManager() {
    for (auto const &maps_map : master_maps_holder_) {
        for (auto const &map : maps_map.second)
            delete (map.second);
    }
}

void MapsManager::ComputeFov(Player_p player, string map_category, short floor) {
    assert(master_maps_holder_.count(map_category) > 0 && master_maps_holder_[map_category].count(floor) >0);

    master_maps_holder_[map_category][floor]->computeFov(player->GetPosition().GetX(),
                                                         player->GetPosition().GetY(),
                                                         player->GetFovRadius());
}

bool MapsManager::IsInFov(size_t x, size_t y, string map_category, short floor) {
    assert(master_maps_holder_.count(map_category) > 0 && master_maps_holder_[map_category].count(floor) >0);
    
    return master_maps_holder_[map_category][floor]->IsInFov(x, y);
}

