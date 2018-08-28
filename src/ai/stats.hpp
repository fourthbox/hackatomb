#ifndef STATS_HPP_
#define STATS_HPP_

/**
 Enumerator that defines the monster tier levels.
 */
enum struct TierLevel {
    TIER_0_ = 0,
    TIER_1_,
    TIER_2_,
    TIER_3_,
    TIER_4_,
    TIER_5_
};

/**
 This struct holds all the stats an actor have
 */
struct Stats {
    std::size_t level_;
    std::size_t str_;
    std::size_t dex_;
    std::size_t con_;
    std::size_t int_;
    std::size_t max_hp_;
    int current_hp_;
    std::size_t max_mp_;
    int current_mp_;
    std::size_t hp_rec_;
    std::size_t mp_rec_;
    std::size_t xp_;
    std::size_t hunger_;
    std::size_t stealth_;
    std::size_t speed_;
    int fov_;
    
    Stats() {
    }
    
    Stats (std::size_t level, std::size_t strength, std::size_t dexterity, std::size_t constitution, std::size_t intelligence, std::size_t max_hp, int current_hp, std::size_t max_mp, int current_mp, std::size_t hp_rec, std::size_t mp_rec, std::size_t xp, std::size_t hunger, std::size_t stealth, int fov, std::size_t speed) :
    str_ {strength},
    dex_ {dexterity},
    con_ {constitution},
    int_ {intelligence},
    max_hp_ {max_hp},
    current_hp_ {current_hp},
    max_mp_ {max_mp},
    current_mp_ {current_mp},
    hp_rec_ {hp_rec},
    mp_rec_ {mp_rec},
    xp_ {xp},
    hunger_ {hunger},
    stealth_ {stealth},
    fov_ {fov},
    speed_ {speed},
    level_ {level} {
    }
    
};

struct MonsterStats : public Stats {
    std::string name_;
    int sprite_;
    TCODColor color_;
    TierLevel tier_level_;
    
    MonsterStats(std::size_t level, std::size_t strength, std::size_t dexterity, std::size_t constitution, std::size_t intelligence, std::size_t max_hp, int current_hp, std::size_t max_mp, int current_mp, std::size_t hp_rec, std::size_t mp_rec, std::size_t xp, std::size_t hunger, std::size_t stealth, int fov, std::size_t speed, std::string name, int sprite, TCODColor color, TierLevel tier_level) :
    Stats(level, strength, dexterity, constitution, intelligence, max_hp, current_hp, max_mp, current_mp, hp_rec, mp_rec, xp, hunger, stealth, fov, speed),
    name_ {name},
    sprite_ {sprite},
    color_ {color},
    tier_level_ {tier_level} {
    }
};

#endif /* STATS_HPP_ */
