#ifndef MONSTER_FACTORY_HPP_
#define MONSTER_FACTORY_HPP_

#include "monster.hpp"

class MonsterFactory {
public:
    MonsterFactory();
    
    /**
     Creates a monster in the specified tier.
     @param x The X coordinate.
     @param y The Y coordinate.
     @param maps_manager The maps manager
     @param tier The selected tier
     @return A unique pointer to the generated monster.
     */
    std::unique_ptr<Monster> BuildMonsterByTier(size_t x, size_t y, MapsManager &maps_manager, TierLevel tier);

    /**
     Creates a goblin in the specified position.
     @param x The X coordinate.
     @param y The Y coordinate.
     @param maps_manager The maps manager
     @return A unique pointer to the generated monster.
     */
    std::unique_ptr<Monster> BuildGoblin(size_t x, size_t y, MapsManager &maps_manager);
    
    /**
     Creates a orc in the specified position.
     @param x The X coordinate.
     @param y The Y coordinate.
     @param maps_manager The maps manager
     @return A unique pointer to the generated monster.
     */
    std::unique_ptr<Monster> BuildOrc(size_t x, size_t y, MapsManager &maps_manager);

private:
    std::unordered_map<TierLevel, std::vector<MonsterStats>> monster_stats_;
};

#endif /* MONSTER_FACTORY_HPP_ */
