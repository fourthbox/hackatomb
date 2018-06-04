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
    void Initialize(ActionManager &action_manager, ActorManager &actor_manager, MapsManager &maps_manager);

    void SetAction(Action action);
    
    void Update();
    void Draw(TCODConsole &console);
    
    void SetupCrossshair(CrosshairMode mode, int range);
    
private:
    std::experimental::optional<size_t> crosshair_x_, crosshair_y_;
    std::experimental::optional<int> range_;
    
    Action action_;
    PathFinder path_finder_;
    CrosshairMode mode_;
    
    ActionManager *action_manager_;
    ActorManager *actor_manager_;
    
    void ResetCrosshair();
    
};

#endif /* AIM_MANAGER_HPP_ */
