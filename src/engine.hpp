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

class Engine {
public:
    // Singleton stuff
    static Engine& GetInstance() {
        static Engine instance;
        return instance;
    }
    Engine(Engine const&) = delete;
    void operator=(Engine const&) = delete;
    
    // Getters and Setters
    constexpr void PlayerPerformedAction() { game_status_ = TurnPhase::ACTION; }
    constexpr RootConsoleManager &GetRootConsoleManager() { return root_console_manager_; }
    
    // Main functions
    void Initialize(std::shared_ptr<libpmg::DungeonMap> map, Player_p player);
    void Initialize(std::shared_ptr<libpmg::WorldMap> map);
    void Update();
    void Render();
    void RenderWorld();
    void ComputeFov();
    Actor_p GetActor(size_t x, size_t y);
    void AddMonster(Actor_p monster);

    // Map Functions
    bool CanMoveToPosition(size_t x, size_t y);
    
    // Enums
    enum struct TurnPhase {
        IDLE,
        ACTION
    };
    
private:
    bool initialized_;
    Engine();
    
    // Entities management
    Player_p player_;
    std::vector<Actor_p> actor_list_;
    
    // Map management
    MapsManager maps_manager_;
    string current_map_category_;
    short current_floor_;
    
    // World management
    std::unique_ptr<World> world_map_;

    // Ui management
    UiManager ui_manager_;
    
    // Game management
    TurnPhase game_status_;
    RootConsoleManager root_console_manager_;
    
    void InitEngine();
    void InitUi();
};

#endif /* ENGINE_HPP_ */
