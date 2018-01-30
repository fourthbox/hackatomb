#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "actor.hpp"

class Player : public Actor {
public:
    Player(size_t x, size_t y, int ch, string &name, const TCODColor &col, Stats &stats);

    int GetFovRadius();
    
private:
    int fov_radius_;
};

typedef std::shared_ptr<Player> Player_p;

#endif /* PLAYER_HPP_ */
