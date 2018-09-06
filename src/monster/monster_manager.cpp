#include "monster_manager.hpp"

#include "engine.hpp"
#include "game_constants.hpp"

struct FloorsTierDistribution {
    int monster_amount_;
    float min_floor_pct_, max_floor_pct_;
    
    FloorsTierDistribution(int monster_amount, float min_floor_pct, float max_floor_pct) :
    monster_amount_ {monster_amount},
    min_floor_pct_ {min_floor_pct},
    max_floor_pct_ {max_floor_pct} {
    }
};

static const std::map<TierLevel, FloorsTierDistribution> kFloorTierConfigs = {
//  {TierLevel, FloorsTierDistribution(monster_amount, min_floor_pct, max_floor_pct)}
    {TierLevel::TIER_0_, FloorsTierDistribution(50, 0.0f, .3)},
    {TierLevel::TIER_1_, FloorsTierDistribution(40, .2, .5)},
    {TierLevel::TIER_2_, FloorsTierDistribution(20, .4, .7)},
    {TierLevel::TIER_3_, FloorsTierDistribution(16, .6, .9)},
    {TierLevel::TIER_4_, FloorsTierDistribution(8, .8, 1.0f)},
    {TierLevel::TIER_5_, FloorsTierDistribution(1, 1.0f, 1.0f)},
};

void MonsterManager::Initialize(ActorManager &actor_manager) {
    assert(!initialized_);
    
    this->actor_manager_ = &actor_manager;
    
    initialized_ = true;
}

void MonsterManager::PopulateMap(MapsManager &maps_manager, DungeonCategory category) {
    assert(initialized_);
    
    /**
     By design doc, the exp distribution must be:
         20% of MAX_POINTS is yold by the last floor boss. (TIER_6)
         20% of MAX_POINTS is yold by exactly 8 2.5% exp monsters.
         20% of MAX_POINTS is yold by exactly 16 1.25% exp monsters.
         20% of MAX_POINTS is yold by exactly 20 1% exp monsters.
         10% of MAX_POINTS is yold by exactly 40 0.25% exp monsters.
         10% of MAX_POINTS is yold by exactly 50 0.2% exp monsters. (TIER_0)
     
     and floor distribusion must be:
         TIER_5 monsters can only appear in the lowest floor (MAX_FLOOR).
         TIER_4 monsters can appear from 80% to MAX_FLOOR.
         TIER_3 monsters can appear from 60% to 90% of MAX_FLOOR.
         TIER_2 monsters can appear from 40% to 70% of MAX_FLOOR.
         TIER_1 monsters can appear from 20% to 50% of MAX_FLOOR.
         TIER_0 monsters can appear from floor 0 to 30% of MAX_FLOOR.
     */
    
    // Generate all the monsters that this dungeon will host, based on
    // the amount of XP that must be yold by the dungeon.
    auto dungeon_maps {maps_manager.GetDungeonByCategory(category)};

    // Cycle all the tiers
    for (auto const &tier : kFloorTierConfigs) {
        // Get min and max floor and the amount of monsters to distribute
        auto monster_amount {tier.second.monster_amount_};
        auto min_floor_pct {tier.second.min_floor_pct_ == 0 ? 0 : kStandardDungeonDepth * tier.second.min_floor_pct_};
        auto max_floor_pct {tier.second.max_floor_pct_ == 1 ? kStandardDungeonDepth : kStandardDungeonDepth * tier.second.max_floor_pct_};
        
        assert(min_floor_pct <= max_floor_pct);

        // Select a random floor within range
        auto rnd_floor {Engine::GetRandomUintFromRange(min_floor_pct, max_floor_pct)};
        
        // Initialize location (position not confirmed yet)
        MapLocation starting_location (category, rnd_floor);
        
        // Check if the selected floor has been loaded
        if (maps_manager.IsFloorLoaded(starting_location)) {
            // Get random position in random room
            starting_location = maps_manager.GetRandomLocation(category, rnd_floor);
        }
        
        // Generate monster
        auto monster {monster_factory_.BuildMonsterByTier(starting_location, maps_manager, tier.first)};

        // Add it to the monster list
        monster_list_.push_back(std::move(monster));
    }
}

void MonsterManager::Draw(TCODConsole &console, Player const &player, MapsManager &maps_manager) {
    assert(initialized_);
    
    for (auto const &monster : monster_list_) {
        if (maps_manager.IsFloorLoaded(monster->GetMapLocation())
            && monster->GetMapLocation().floor_ == player.GetMapLocation().floor_
            && (monster->IsPermaVisible() || maps_manager.IsInFov((Actor&)player, monster->GetMapLocation()))) {
            monster->Draw(console);
        }
    }
}

void MonsterManager::TogglePermaVisible(bool is_perma_visible, Monster *monster) const {
    assert(initialized_);

    if (monster == nullptr) {
        for (auto const &monster : monster_list_) {
            monster->TogglePermaVisible(is_perma_visible);
        }
    } else {
        monster->TogglePermaVisible(is_perma_visible);
    }
}

void MonsterManager::Update(size_t speed, ActionManager &action_manager, MapsManager &maps_manager) const {
    assert(initialized_);
    
    for (auto const &monster : monster_list_) {
        if (maps_manager.IsFloorLoaded(monster->GetMapLocation()))
            monster->Update(speed, action_manager, maps_manager);
    }
}

Monster *MonsterManager::GetMonsterByCoordinates(size_t x, size_t y) const {
    for (auto const &monster : monster_list_) {
        if (monster->GetPosition().first == x && monster->GetPosition().second == y) {
            return monster.get();
        }
    }
    
    return nullptr;
}

std::vector<Actor*> MonsterManager::GetMonsterList() const {
    assert (initialized_);
    
    std::vector<Actor*> new_list;
    
    for (auto const &monster : monster_list_)
        new_list.push_back(monster.get());
    
    return new_list;
}

void MonsterManager::NewFloorLoaded(MapsManager &maps_manager) {
    assert(initialized_);
    
    for (auto const &monster : monster_list_) {
        if (auto location {monster->GetMapLocation()};
            maps_manager.IsFloorLoaded(location)
            && location.x_ == -1
            && location.y_ == -1) {
            
            // Get random position in random room
            auto starting_location {maps_manager.GetRandomLocation(location.dungeon_category_, location.floor_)};
            
            // Move monster to new location
            monster->LoadIntoLocation(starting_location, maps_manager);
        }
    }
}
