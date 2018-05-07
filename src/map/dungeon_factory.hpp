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
    
    std::shared_ptr<libpmg::DungeonMap> GenerateDungeon(DungeonCategory const &category);
    
private:
    std::unordered_map<DungeonCategory, std::unique_ptr<libpmg::DungeonBuilder>> category_builders_;
    
};

#endif /* DUNGEON_FACTORY_HPP_ */