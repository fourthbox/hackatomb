/**
 This class manages the initialization, draw and management of the dungeon maps.
 @file maps_manager.hpp
 @author pat <pat@fourthbox.com>
 */

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
    MapsManager();
    void Initialize();
    void Draw(string map_category, short floor, std::shared_ptr<TCODConsole> console);

    void AddMapToMaster(std::unique_ptr<Map> map, string map_category, short floor = -1);
    bool CanMoveToPosition(size_t x, size_t y, string map_category, short floor);
    void ComputeFov(Player_p player, string map_category, short floor);
    bool IsInFov(size_t x, size_t y, string map_category, short floor);
    void SetCurrentMap(string current_map_category, short current_floor);
    
private:
    bool initialized_;

    std::unordered_map<string, std::map< size_t, std::unique_ptr<Map> > > master_maps_holder_;   /**< The key is the map category. the value is is an ordered Map in which the key is the floor number, and the value is the Map itself. */

};
#endif /* MAPS_MANAGER_HPP_ */
