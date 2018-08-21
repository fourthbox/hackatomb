#ifndef DUNGEON_FACTORY_HPP_
#define DUNGEON_FACTORY_HPP_

#include <unordered_map>

#include "libpmg.hpp"

/**
 Enumerator that defines the dungeon categories.
 */
enum struct DungeonCategory {
    NORMAL_,
    FIRE_,
    ICE_,
    FOREST_,
    UNDEAD_
};

class DungeonFactory {
public:
    DungeonFactory();
    
    std::shared_ptr<libpmg::DungeonMap> BuildDungeon(DungeonCategory const &category, int floor);
    
private:
    std::unordered_map<DungeonCategory, std::unique_ptr<libpmg::DungeonBuilder>> category_builders_;
    
    void SetupBuilder(libpmg::DungeonBuilder &builder);
};

#endif /* DUNGEON_FACTORY_HPP_ */
