#include "monster_factory.hpp"

#include "bestiary.hpp"
#include "engine.hpp"

MonsterFactory::MonsterFactory() {
    // TIER_0
    std::vector<MonsterStats> tier_0 {
        RatStats()
    };
    // TIER_1
    std::vector<MonsterStats> tier_1 {
        WolfStats()
    };
    // TIER_2
    std::vector<MonsterStats> tier_2 {
        GoblinStats()
    };
    // TIER_3
    std::vector<MonsterStats> tier_3 {
        OrcStats()
    };
    // TIER_4
    std::vector<MonsterStats> tier_4 {
        TrollStats()
    };
    // TIER_5
    std::vector<MonsterStats> tier_5 {
        DragonStats()
    };
    
    monster_stats_[TierLevel::TIER_0_] = tier_0;
    monster_stats_[TierLevel::TIER_1_] = tier_1;
    monster_stats_[TierLevel::TIER_2_] = tier_2;
    monster_stats_[TierLevel::TIER_3_] = tier_3;
    monster_stats_[TierLevel::TIER_4_] = tier_4;
    monster_stats_[TierLevel::TIER_5_] = tier_5;
}

std::unique_ptr<Monster> MonsterFactory::BuildMonsterByTier(size_t x, size_t y, MapsManager &maps_manager, TierLevel tier) {
    auto monster {std::make_unique<Monster>()};
    
    auto monstersTier {&monster_stats_[tier]};
    auto rndIndex {Engine::GetRandomUintFromRange(0, monstersTier->size()-1)};
    
    monster->Initialize(x, y, monster_stats_[tier][rndIndex], maps_manager);
    
    return std::move(monster);
}

std::unique_ptr<Monster> MonsterFactory::BuildGoblin(size_t x, size_t y, MapsManager &maps_manager) {
    auto monster {std::make_unique<Monster>()};
    
    monster->Initialize(x, y, kGoblinStats, maps_manager);
    
    return std::move(monster);
}

std::unique_ptr<Monster> MonsterFactory::BuildOrc(size_t x, size_t y, MapsManager &maps_manager) {
    auto monster {std::make_unique<Monster>()};
    
    monster->Initialize(x, y, kOrcStats, maps_manager);
    
    return std::move(monster);
}
