#ifndef BESTIARY_HPP_
#define BESTIARY_HPP_

#include "stats.hpp"

struct RatStats : public MonsterStats {
    RatStats() :
    MonsterStats (
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
                  "rat", // name
                  'r', // sprite
                  TCODColor::lightestGrey, // sprite color
                  TierLevel::TIER_0_
                  ) {
    }
};

const struct WolfStats : public MonsterStats {
    WolfStats() :
    MonsterStats (
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
                  "golf", // name
                  'w', // sprite
                  TCODColor::darkestGrey, // sprite color
                  TierLevel::TIER_1_
                  ) {
    }
} kWolfStats;

const struct GoblinStats : public MonsterStats {
    GoblinStats() :
    MonsterStats (
                  1, //lvl
                  10, //str
                  2, //dex
                  10, //con
                  3, //int
                  10, //max_hp
                  10, //current_hp
                  0, //max_mp
                  0, //current_mp
                  0, //hp_rec
                  0, //mp_rec
                  10, //xp
                  0, //hunger
                  0, //stealth
                  10,//fov
                  2, //speed
                  "goblin", // name
                  'g', // sprite
                  TCODColor::lighterGreen, // sprite color
                  TierLevel::TIER_2_
                  ) {
    }
} kGoblinStats;

const struct OrcStats : public MonsterStats {
    OrcStats() :
    MonsterStats (
                  1, //lvl
                  10, //str
                  2, //dex
                  10, //con
                  3, //int
                  10, //max_hp
                  10, //current_hp
                  0, //max_mp
                  0, //current_mp
                  0, //hp_rec
                  0, //mp_rec
                  10, //xp
                  0, //hunger
                  0, //stealth
                  10,//fov
                  2, //speed
                  "orc", // name
                  'O', // sprite
                  TCODColor::darkerGreen, // sprite color
                  TierLevel::TIER_3_
                  ) {
    }
} kOrcStats;

const struct TrollStats : public MonsterStats {
    TrollStats() :
    MonsterStats (
                  1, //lvl
                  10, //str
                  2, //dex
                  10, //con
                  3, //int
                  10, //max_hp
                  10, //current_hp
                  0, //max_mp
                  0, //current_mp
                  0, //hp_rec
                  0, //mp_rec
                  10, //xp
                  0, //hunger
                  0, //stealth
                  10,//fov
                  2, //speed
                  "troll", // name
                  'T', // sprite
                  TCODColor::darkYellow, // sprite color
                  TierLevel::TIER_4_
                  ) {
    }
} kTrollStats;

const struct DragonStats : public MonsterStats {
    DragonStats() :
    MonsterStats (
                  1, //lvl
                  10, //str
                  2, //dex
                  10, //con
                  3, //int
                  10, //max_hp
                  10, //current_hp
                  0, //max_mp
                  0, //current_mp
                  0, //hp_rec
                  0, //mp_rec
                  10, //xp
                  0, //hunger
                  0, //stealth
                  10,//fov
                  2, //speed
                  "dragon", // name
                  'D', // sprite
                  TCODColor::darkerRed, // sprite color
                  TierLevel::TIER_5_
                  ) {
    }
} kDragonStats;

#endif /* BESTIARY_HPP_ */
