/**
 @file actor_manager.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef ACTOR_MANAGER_HPP_
#define ACTOR_MANAGER_HPP_

#include <vector>

#include "monster_manager.hpp"
#include "player_manager.hpp"

/**
 This class is responsable for the maangement and initialization of every actor in the loaded game.
 */
class ActorManager : public InitiableObject {
public:
    void Initialize();
    
    /**
     Draw all monsters on the current floor.
     @param console The console to drow upon.
     @param maps_manager The maps manager.
     */
    void DrawMonsters(TCODConsole &console, MapsManager &maps_manager);
    
    /**
     Draw the player.
     @param console The console to drow upon.
     */
    void DrawPlayer(TCODConsole &console);
    
    /**
     Initialize the monster manager.
     @param action_manager The action manager.
     @param maps_manager The maps manager.
     */
    void InitializeMonsterManager(ActionManager &action_manager, MapsManager &maps_manager);

    /**
     Initialize the player and place it in its starting position.
     @param start_position The start position coordinates.
     @param action_manager The action manager.
     @param maps_manager The maps manager.
     */
    void InitializePlayer(Coordinate start_position, ActionManager &action_manager, MapsManager &maps_manager);

    /**
     Cycles the actor list and return the actor on the specified coordinates.
     Unless specified, it looks on the current floor only.
     @param x The X coordinate.
     @param y The Y coordinate.
     @return A pointer to the actor if an actor is find, nullptr otherwise.
     */
    Actor *GetActorByCoordinates(size_t x, size_t y);
    
    /**
     Gett all the actors on this floow.
     @return A vector of pointers to actors..
     */
    std::vector<Actor*> GetAllActors();
    
    /**
     Get the player.
     @return Return the player by reference.
     */
    inline Player &GetPlayer() { return player_manager_.GetPlayer(); }
    
    /**
     Populates the dungeon map with all monsters and NPCs
     @param maps_manager The Maps Manager
     @param category The selected dungeon category to populate
     */
    void PopulateMap(MapsManager &maps_manager, DungeonCategory category);
    
    /**
     Set all monsters on the floor to be visible
     */
    void SetAllMonstersVisible() const;
        
    /**
     Call for Update() on every actor in actor_list_
     @param speed The speed of this update cycle.
     @param action_manager The action manager.
     @param maps_manager The maps manager.
     */
    void Update(size_t speed, ActionManager &action_manager, MapsManager &maps_manager);
    
private:
    PlayerManager player_manager_;     /**< The PlayerManager */
    MonsterManager monster_manager_;     /**< The MonsterManager */
};

#endif /* ACTOR_MANAGER_HPP_ */
