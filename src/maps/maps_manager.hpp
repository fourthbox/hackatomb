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

/**
 Class responsable for the management and initialization of every dungeon map.
 Every Map belong to a specific map category, and has a specific floor.
 */
class MapsManager {
public:
    MapsManager();
    
    /**
     Initialized this instance.
     */
    void Initialize();
    
    /**
     Draws a specific Map on a specific console.
     @param map_category The category the map belongs to.
     @param floor The floor the map belongs to.
     @param console The console upon which to draw the map.
     */
    void Draw(std::string map_category, short floor, std::shared_ptr<TCODConsole> console);

    /**
     It will add the map to the map holder. There's no check for duplicates, and maps can override existing slots.
     @param map The map to store.
     @param map_category The map category this map belongs to.
     @param floor The floor this map belongs to. If floor is -1, it will assign the map with the lowest floor, and append it to the map golder. Default value: -1.
     */
    void AddMapToMaster(std::unique_ptr<Map> map, std::string map_category, short floor = -1);
    
    /**
     Check whether the specified position is walkable or not.
     @param x The X coordinate.
     @param y The Y coordinate.
     @param map_category The map category the specified coordinates belongs to.
     @param floor The floor the specified coordinates belongs to.
     @return True if the player can move to the specified position, false otherwise.
     */
    bool CanMoveToPosition(size_t x, size_t y, std::string map_category, short floor);
    
    /**
     Check whether the specified position is walkable or not.
     @param x The X coordinate.
     @param y The Y coordinate.
     @param map_category The map category the specified coordinates belongs to.
     @param floor The floor the specified coordinates belongs to.
     @return True if the player can move to the specified position, false otherwise.
     */
    void ComputeFov(Player_p player, std::string map_category, short floor);
    
    /**
     Check whether the specified position is walkable or not.
     @param x The X coordinate.
     @param y The Y coordinate.
     @param map_category The map category the specified coordinates belongs to.
     @param floor The floor the specified coordinates belongs to.
     @return True if the player can move to the specified position, false otherwise.
     */
    bool IsInFov(size_t x, size_t y, std::string map_category, short floor);
        
private:
    bool initialized_;      /**< Utility switch for initialization security checks. */

    std::unordered_map<std::string, std::map< size_t, std::unique_ptr<Map> > > master_maps_holder_;   /**< The key is the map category. the value is is an ordered Map in which the key is the floor number, and the value is the Map itself. */

};
#endif /* MAPS_MANAGER_HPP_ */
