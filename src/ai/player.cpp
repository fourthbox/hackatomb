#include "player.hpp"

#include "game_constants.hpp"

Player::Player(size_t x, size_t y, int ch, string &name, const TCODColor &col, Stats &stats) :
    Actor {x, y, ch, name, col, stats},
    fov_radius_ {kDefaultFovRadius}
{}

int Player::GetFovRadius() {    
    return fov_radius_;
}
