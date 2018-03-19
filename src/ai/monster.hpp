/**
 @file monster.hpp
 @author pat <pat@fourthbox.com>
 */

#ifndef MONSTER_HPP_
#define MONSTER_HPP_

#include "actor.hpp"

class Monster : public Actor {
public:
    /**
     Update the player based on the action.
     */
    void Update() override;

};

#endif /* MONSTER_HPP_ */
