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
     @param floor The floor this map belongs to. If floor is -1, it will assign the map with the lowest floor, and append it to the map golder. Default value: -1.
     */
    void AddMapToMaster(std::unique_ptr<Map> map, DungeonCategory map_category, int floor = -1);
    
    void LoadDungeonFloor(DungeonCategory category, int floor);
    
    /**
     Check whether the specified position is walkable or not.
     @param x The X coordinate.
     @param y The Y coordinate.
     @return True if the player can move to the specified position, false otherwise.
     */
    bool IsTileWalkable(size_t x, size_t y);
    
    /**
     Check whether the specified position is in the field of view or not.
     @param map_location The map location.
     @return True if the specified position is in the field of view, false otherwise.
     */
    bool IsInFov(Actor const &actor, MapLocation const &map_location);
    
    /**
     Compute the field of view of the specified actor.
     @param player The player.
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
     @param room_number The room number from which the random position is taken. -1 (default) is random room
     @param floor_number The floor number from which the random position is taken. -1 (default) is current floor
     @return A randoom coordinate
     */
    std::pair<size_t, size_t> GetRandomPosition(int room_number = -1, int floor_number = -1);
    size_t GetRandomRoom();
    
    Tile *GetTileFromFloor(size_t x, size_t y, int floor = -1);
    
    std::unique_ptr<TCODPath> AllocatePathFromCurrentFloor(ITCODPathCallback const *callback, float diagonal_cost);
    
    void SetAllExplored();
    
    bool IsInteractable(size_t x, size_t y);
    void OpenDoor(size_t x, size_t y);
    
    Coordinate_opt MoveToFloor(bool is_upstairs);
    Coordinate_opt GetEntrancePosition();
    Coordinate_opt GetExitPosition();
    
    inline int GetCurrentFloor() const { return current_floor_; }
    
private:
    DungeonCategory current_map_category_;      /**< Dungeon type. */
    int current_floor_;                   /**< Current floor. */
    DungeonFactory dungeon_factory_;
    ItemsFactory items_factory_;
    std::unordered_map<DungeonCategory, std::map< size_t, std::unique_ptr<Map>> > master_maps_holder_;   /**< The key is the map category. the value is is an ordered Map in which the key is the floor number, and the value is the Map itself. */
    
    bool need_refresh_;
};

#endif /* MAPS_MANAGER_HPP_ */
