#ifndef AIM_MANAGER_HPP_
#define AIM_MANAGER_HPP_

#include <experimental/optional>

#include "action_manager.hpp"
#include "game_globals.hpp"
#include "libtcod.hpp"
#include "path_finder.hpp"
#include "player.hpp"

enum struct CrosshairMode {
    NONE_,
    ARROW_,
    BEAM_,
    CONE_,
    BALL_,
    LOLLIPOP_
};

class AimManager : public InitiableObject {
public:
    AimManager();
    void Initialize(DungeonCategory const &category, std::size_t const &floor, MapsManager &maps_manager);
    
    /**
     Draw the crosshair on position.
     @param console The player.
     @param player_position The player map location.
     */
    void DrawCrosshair(TCODConsole &console, MapLocation const &player_position);

    /**
     Draw the trail highlight of the crosshair.
     @param console The player.
     @param player_position The player map location.
     */
    void DrawTrail(TCODConsole &console, MapLocation const &player_position);
    
    /**
     Reset the crosshair, disabling it.
     */
    void ResetCrosshair();

    /**
     Set the action to the selected one.
     @param action The selected action.
     */
    void SetAction(Action action);
    
    /**
     Setup the crosshair and place it to the closest enemy, if possible, or on the player otherwise.
     @param mode The crosshair mode.
     @param range The max range of the crosshair.
     @param player The player.
     @param actor_list The list of actors on the current floor.
     @param maps_manager The maps manager.
     */
    void SetupCrossshair(CrosshairMode mode, int range, Player &player, std::vector<Actor*> actor_list, MapsManager &maps_manager);
    
    /**
     Update the crosshair position.
     @param player The player.
     @param action_manager The action manager.
     @param maps_manager The maps manager.
     */
    void Update(Player const &player, ActionManager &action_manager, MapsManager &maps_manager);
    
    /**
     Returns the current crosshair location.
     @return The current crosshair location on the map.
     */
    MapLocation const &GetCrosshairLocation() const;

private:
    std::experimental::optional<MapLocation> crosshair_location_;
    std::experimental::optional<int> range_;
    
    Action action_;
    PathFinder path_finder_;
    CrosshairMode mode_;
    
};

#endif /* AIM_MANAGER_HPP_ */
