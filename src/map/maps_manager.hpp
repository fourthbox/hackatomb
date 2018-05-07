/**
 This class manages the initialization, draw and management of the dungeon maps.
 @file maps_manager.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef MAPS_MANAGER_HPP_
#define MAPS_MANAGER_HPP_

#include <map>

#include "dungeon_factory.hpp"
#include "initiable_object.hpp"
#include "map.hpp"

class Actor;

/**
 Class responsable for the management and initialization of every dungeon map.
 Every Map belong to a specific map category, and has a specific floor.
 */
class MapsManager : public InitiableObject {
public:
    DungeonCategory current_map_category_;      /**< Dungeon type. */
    short current_floor_;                   /**< Current floor. */

    /**
     Initialized this instance.
     */
    void Initialize();
    
    /**
     Draws a specific Map on a specific console.
     @param console The console upon which to draw the map.
     */
    void Draw(TCODConsole &console, Actor const &actor);

    /**
     It will add the map to the map holder. There's no check for duplicates, and maps can override existing slots.
     @param map The map to store.
     @param map_category The map category this map belongs to.
     @param floor The floor this map belongs to. If floor is -1, it will assign the map with the lowest floor, and append it to the map golder. Default value: -1.
     */
    void AddMapToMaster(std::unique_ptr<Map> map, DungeonCategory map_category, short floor = -1);
    
    /**
     Check whether the specified position is walkable or not.
     @param x The X coordinate.
     @param y The Y coordinate.
     @param map_category The map category the specified coordinates belongs to.
     @param floor The floor the specified coordinates belongs to.
     @return True if the player can move to the specified position, false otherwise.
     */
    bool CanMoveToPosition(size_t x, size_t y);
    
    /**
     Compute the field of view of the specified actor.
     @param player The player.
     */
    void ComputeFov(Actor const &actor);
    
    /**
     Check whether the specified position is in the field of view or not.
     @param x The X coordinate.
     @param y The Y coordinate.
     @return True if the specified position is in the field of view, false otherwise.
     */
    bool IsInFov(size_t x, size_t y);
    
    std::pair<size_t, size_t> GetRandomPosition(int room_number = -1);
    
    std::unique_ptr<TCODPath> AllocatePathFromCurrentFloor(ITCODPathCallback const *callback, float diagonal_cost);
    
    void SetAllExplored();
    
    bool IsInteractable(size_t x, size_t y);
    void OpenDoor(size_t x, size_t y);
    
private:
    DungeonFactory dungeon_factory_;
    std::unordered_map<DungeonCategory, std::map< size_t, std::unique_ptr<Map>> > master_maps_holder_;   /**< The key is the map category. the value is is an ordered Map in which the key is the floor number, and the value is the Map itself. */

};

#endif /* MAPS_MANAGER_HPP_ */
