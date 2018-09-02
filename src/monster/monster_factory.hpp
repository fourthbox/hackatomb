#ifndef MONSTER_FACTORY_HPP_
#define MONSTER_FACTORY_HPP_

#include "monster.hpp"

class MonsterFactory {
public:
    MonsterFactory();
    
    /**
     Creates a monster in the specified tier.
     @param map_location The map location.
     @param maps_manager The maps manager
     @param tier The selected tier
     @return A unique pointer to the generated monster.
     */
    std::unique_ptr<Monster> BuildMonsterByTier(MapLocation const &map_location, MapsManager &maps_manager, TierLevel tier);

private:
    std::unordered_map<TierLevel, std::vector<MonsterStats>> monster_stats_;
};

#endif /* MONSTER_FACTORY_HPP_ */
