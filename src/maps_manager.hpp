#ifndef MAPS_MANAGER_HPP_
#define MAPS_MANAGER_HPP_

#include <map>
#include <string>
#include <unordered_map>

#include "player.hpp"
#include "map.hpp"
#include "map_builder.hpp"

class MapsManager {
public:
    void AddMapToMaster(Map *map, string map_category, short floor = -1);
    bool CanMoveToPosition(size_t x, size_t y, string map_category, short floor);
    void Draw(string map_category, short floor);
    void ComputeFov(Player_p player, string map_category, short floor);
    bool IsInFov(size_t x, size_t y, string map_category, short floor);
    void SetCurrentMap(string current_map_category, short current_floor);

    ~MapsManager();
    
private:
    std::unordered_map<
        string,
        std::map<size_t, Map*>> master_maps_holder_;
};
#endif /* MAPS_MANAGER_HPP_ */
