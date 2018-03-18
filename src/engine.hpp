/**
 Main class responsible for the management of everything, from the start to the end of the game.
 @file engine.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "player.hpp"
#include "map_builder.hpp"
#include "maps_manager.hpp"
#include "root_console_manager.hpp"
#include "ui_manager.hpp"
#include "world.hpp"

/**
 The main class. It must be initialized before every operation, because it will initialize every needed component.
 Update() and Render() will updare and render every needed component.
 */
class Engine : public InitiableObject{
public:
    // Getters and Setters
//    constexpr void PlayerPerformedAction() { game_status_ = TurnPhase::ACTION; }
    
    /**
     Initialize every component of this class. Add the first map to the MapsManager and place the player into the map.
     @param map The first map to add to the MapsManager
     @param player The player
     */
    void Initialize(std::shared_ptr<libpmg::DungeonMap> map, Player_p player);
    void Initialize(std::shared_ptr<libpmg::WorldMap> map); // TODO: this is just temporary
    
    /**
     At the beginning of the function the game is put in an TurnPhase::IDLE state. Then the Update() for the player is called.
     If the player performed an action that consumes 1 turn, then the function will proceed to call the Update() from all other actors in the map.
     */
    void Update();
    
    /**
     Calls the draw function on every component, then tells the RootConsoleManager to blit every console on the root console.
     */
    void Render();
    void RenderWorld(); // TODO: temporary design
    
//    Actor_p GetActor(size_t x, size_t y);
    void AddMonster(Actor_p monster);   //TODO: temporary design
//    bool CanMoveToPosition(size_t x, size_t y);
    
    /**
     Enumerator that defines the phases of the turn.
     */
    enum struct TurnPhase {
        IDLE,   /**< The game is idle. Waiting for a player input to procede. */
        ACTION  /**< The player has performed an action. Every actor will perform an action. */
    };
    
private:
    // Entities management
    Player_p player_;                   /**< Pointer to the player. */
    std::vector<Actor_p> actor_list_;   /**< List of pointers to every actor, excluding the player. */
    
    // Map management
    MapsManager maps_manager_;          /**< The manager for the maps used in the game */
    
    // World management
    std::unique_ptr<World> world_map_;  /**< Pointer to the current world map */

    // Ui management
    UiManager ui_manager_;              /**< The manager for everything UI */
    
    // Game management
    TurnPhase game_status_;             /**< Keeps track of the current TurnPhase */
    RootConsoleManager root_console_manager_;   /**< Manager for the root console. It is responsable for drawing every console on the main one */
    
    /**
     Initialize the components for the engine.
     */
    void InitEngine();
    
    /**
     Initialize the components for the UI.
     */
    void InitUi();
    
    /**
     Initialize the Fov, by executing it.
     */
    void InitFov();
};

#endif /* ENGINE_HPP_ */
