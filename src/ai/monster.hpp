/**
 @file monster.hpp
 @author pat <pat@fourthbox.com>
 */

#include "actor.hpp"

#ifndef MONSTER_HPP_
#define MONSTER_HPP_

class Monster : public Actor {
public:
    /**
     Update the player based on the action.
     */
    void Update() override;

};

#endif /* MONSTER_HPP_ */
