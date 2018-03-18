#include "player.hpp"

#include <cassert>

#include "game_constants.hpp"

Player::Player() :
fov_radius_ {kDefaultFovRadius} {
    assert(!initialized_);
}

void Player::Update() {
    assert(initialized_);
}

int Player::GetFovRadius() {
    assert(initialized_);

    return fov_radius_;
}
