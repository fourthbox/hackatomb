#ifndef MONSTER_MANAGER_HPP_
#define MONSTER_MANAGER_HPP_

#include "monster_factory.hpp"

class Player;

class MonsterManager : public InitiableObject {
public:
    void Initialize(ActorManager &actor_manager);
    
    /**
     Draw all the monsters on the specified console.
     @param console The consone upon which to draw.
     @param player The player.
     @param maps_manager The maps manager.
     */
    void Draw(TCODConsole &console, Player const &player, MapsManager &maps_manager);
    
    /**
     Get a monster by the coordinates on the current floor, if present.
     @param x The X coordinate.
     @param y The Y coordinate.
     @return Returns a pointer to the monster. nullptr if no monster is present to the specified location.
     */
    Monster *GetMonsterByCoordinates(size_t x, size_t y) const;
    
    /**
     Populate the dungeon with monsters
     @param maps_manager The Maps Manager
     @param category The selected dungeon category to populate
     */
    void PopulateMap(MapsManager &maps_manager, DungeonCategory category);
    
    /**
     Triggered when a new floor has been loaded.
     It forces to check every actor and get a starting position for the unpositioned ones.
     @param maps_manager The Maps Manager
     */
    void NewFloorLoaded(MapsManager &maps_manager);

    /**
     Toggle one or every monster to be always visible.
     @param is_perma_visible If true, the monsters will be set to always visible.
     @param monster The monster upon which to toggle the visibility.
     */
    void TogglePermaVisible(bool is_perma_visible, Monster *monster = nullptr) const;
    
    /**
     Update the monster ai. Eventually perform an action.
     @param speed The speed of this update cycle.
     @param action_manager The action manager.
     @param maps_manager The maps manager.
     */
    void Update(size_t speed, ActionManager &action_manager, MapsManager &maps_manager) const;
        std::vector<Actor*> GetMonsterList() const;

private:
    ActorManager *actor_manager_;
    
    MonsterFactory monster_factory_;
    std::vector<std::unique_ptr<Monster>> monster_list_;
};

#endif /* MONSTER_MANAGER_HPP_ */
