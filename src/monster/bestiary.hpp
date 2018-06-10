#ifndef BESTIARY_HPP_
#define BESTIARY_HPP_

#include "stats.hpp"

const struct GoblinStats {
    const std::string name_ = "goblin";
    
    const Stats stats_ {
        1, //lvl
        5, //str
        5, //dex
        5, //con
        5, //int
        5, //max_hp
        5, //current_hp
        0, //max_mp
        0, //current_mp
        0, //hp_rec
        0, //mp_rec
        5, //xp
        0, //hunger
        0, //stealth
        10,//fov
        3, //speed
    };
    
    const int sprite_ = 'g';
    const TCODColor color_ = TCODColor::green;
    
} kGoblinStats;

#endif /* BESTIARY_HPP_ */
