/**
 Main class responsible for the management of everything, from the start to the end of the game.
 @file engine.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "action_manager.hpp"
#include "actor_manager.hpp"
#include "input_manager.hpp"
#include "libpmg.hpp"
#include "maps_manager.hpp"
#include "player.hpp"
#include "player_manager.hpp"
#include "root_console_manager.hpp"
#include "start_screen.hpp"
#include "ui_manager.hpp"
#include "world.hpp"

/**
 The main class. It must be initialized before every operation, because it will initialize every needed component.
 Update() and Render() will updare and render every needed component.
 */
class Engine {
public:
    Engine();
    
    /**
     Initialize every component of this class.
     */
    void InitializeGame();
    
    void InitializeStartScreen();
    
    /**
     At the beginning of the function the game is put in an TurnPhase::IDLE_ state. Then the Update() for the player is called.
     If the player performed an action that consumes 1 turn, then the function will proceed to call the Update() from all other actors in the map.
     */
    void Update();
    
    void UpdateStartScreen();
    
    /**
     Calls the draw function on every component, then tells the RootConsoleManager to blit every console on the root console.
     */
    void Render();
    
    void RenderStartScreen();
    
    inline bool IsPlaying() { return is_playing_; }
    inline void StartGame() { is_playing_ = true; }
    
    static size_t GetRandomUintFromRange(size_t min, size_t max) { return libpmg::RndManager::GetInstance().GetRandomUintFromRange(min, max); }
    static size_t GetRandomPercentage() { return GetRandomUintFromRange(0, 100); }
    
private:
    bool start_screen_initialized_;
    bool game_initialized_;
    bool is_playing_;
    
    // Entities management
    ActorManager actor_manager_;        /**< Manager for all actors of the loaded game */
    
    // Map management
    MapsManager maps_manager_;          /**< The manager for the maps used in the game */
    
    // Ui management
    UiManager ui_manager_;              /**< The manager for everything UI */
    
    // Start Screen
    StartScreen start_screen_;
    
    // Game management
    RootConsoleManager root_console_manager_;   /**< Manager for the root console. It is responsable for drawing every console on the main one */
    ActionManager action_manager_; /**< Manager for every movement, attack or interaction done by an actor */
    InputManager input_manager_;        /**< Manager for keyboard and mouse inputs */
    
    void GameOver();
};

#endif /* ENGINE_HPP_ */
