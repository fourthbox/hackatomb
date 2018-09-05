/**
 This class manages the initialization, draw and management of the dungeon maps.
 @file maps_manager.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef MAPS_MANAGER_HPP_
#define MAPS_MANAGER_HPP_

#include <map>

#include "dungeon_factory.hpp"
#include "items_factory.hpp"
#include "map.hpp"

class Actor;

/**
 Class responsable for the management and initialization of every dungeon map.
 Every Map belong to a specific map category, and has a specific floor.
 */
class MapsManager : public InitiableObject {
public:
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
     @param floor The floor this map belongs to. If floor is -1, it will assign the map with the lowest floor, and append it to the map keeper. Default value: -1.
     */
    void AddMapToMaster(std::unique_ptr<Map> map, DungeonCategory map_category, int floor = -1);
    
    void LoadDungeonFloor(DungeonCategory category, int floor);
    
    /**
     Check whether the specified position is walkable or not.
     @param location The location on the map.
     @return True if the player can move to the specified position, false otherwise.
     */
    bool IsTileWalkable(MapLocation const &location);
    
    /**
     Check whether the specified position is in the field of view or not.
     @param map_location The map location.
     @return True if the specified position is in the field of view, false otherwise.
     */
    bool IsInFov(Actor const &actor, MapLocation const &map_location);
    
    /**
     Compute the field of view of the specified actor.
     @param actor The actor to compute.
     */
    void ComputeFov(Actor const &actor);
    
    /**
     Get a dictionary containing all the dungeon floors, by category.
     @param category The category of the dungeon to retreive
     @return A pointer to a dictionary containing all the dungeon floors
     */
    std::map<size_t, std::unique_ptr<Map>> *GetDungeonByCategory(DungeonCategory category);
    
    /**
     Get a random position from a room.
     @param category The map category.
     @param floor The floor of the map.
     @param room_number The room number from which the random position is taken. -1 (default) is random room
     @return A randoom map location
     */
    MapLocation GetRandomLocation(DungeonCategory const &category, std::size_t const &floor, int room_number = -1);
    
    size_t GetRandomRoom();
    
    Tile *GetTileFromFloor(MapLocation const &location);
    
    std::unique_ptr<TCODPath> AllocatePathFromFloor(DungeonCategory const &category, std::size_t const &floor, ITCODPathCallback const *callback, float diagonal_cost);
    
    void SetAllExplored(DungeonCategory const &category, std::size_t const &floor);
    
    bool IsInteractable(MapLocation const &location);
    void OpenDoor(MapLocation const &location);
    
    /**
     Setup a new floor asyncronously, if needed.
     @param current_location The current loaded floor
     @param is_upstairs True, if it's going upstairs, false otherwise
     */
    MapLocation_opt MoveToFloor(MapLocation const &current_location, bool is_upstairs);
    
    MapLocation_opt GetEntrancePosition(MapLocation const &location);
    MapLocation_opt GetExitPosition(MapLocation const &location);

private:
    DungeonFactory dungeon_factory_;
    ItemsFactory items_factory_;
    std::unordered_map<DungeonCategory, std::map< size_t, std::unique_ptr<Map>> > master_maps_holder_;   /**< The key is the map category. the value is is an ordered Map in which the key is the floor number, and the value is the Map itself. */
    
    bool need_refresh_;
};

#endif /* MAPS_MANAGER_HPP_ */
