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
    void Initialize(MapsManager &maps_manager);

    void SetAction(Action action);
    
    void Update(Player const &player, ActionManager &action_manager, MapsManager &maps_manager);
    void DrawTrail(TCODConsole &console, Coordinate player_position);
    void DrawCrosshair(TCODConsole &console, Coordinate player_position);
    
    void SetupCrossshair(CrosshairMode mode, int range, Player &player, std::vector<Actor*> actor_list, MapsManager &maps_manager);
    
    void ResetCrosshair();
    Coordinate GetCrosshairLocation() const;

private:
    std::experimental::optional<size_t> crosshair_x_, crosshair_y_;
    std::experimental::optional<int> range_;
    
    Action action_;
    PathFinder path_finder_;
    CrosshairMode mode_;
    
};

#endif /* AIM_MANAGER_HPP_ */
