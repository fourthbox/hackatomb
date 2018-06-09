#ifndef AIM_MANAGER_HPP_
#define AIM_MANAGER_HPP_

#include <experimental/optional>

#include "action_manager.hpp"
#include "game_globals.hpp"
#include "libtcod.hpp"
#include "path_finder.hpp"

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
    
    void Update(ActionManager &action_manager, ActorManager &actor_manager, MapsManager &maps_manager);
    void DrawTrail(TCODConsole &console, ActorManager &actor_manager);
    void DrawCrosshair(TCODConsole &console, ActorManager &actor_manager);
    
    void SetupCrossshair(CrosshairMode mode, int range, ActorManager &actor_manager, MapsManager &maps_manager);
    
    void ResetCrosshair();
    void PerformActionOnCrosshair(ActionManager &action_manager, ActorManager &actor_manager);
    
private:
    std::experimental::optional<size_t> crosshair_x_, crosshair_y_;
    std::experimental::optional<int> range_;
    
    Action action_;
    PathFinder path_finder_;
    CrosshairMode mode_;
    
};

#endif /* AIM_MANAGER_HPP_ */
