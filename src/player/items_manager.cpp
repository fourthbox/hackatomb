#include "items_manager.hpp"

ItemsManager::ItemsManager() {
    // Initialize every slot to nullptr
    for (auto &slot : inventory_slots_) {
        slot = nullptr;
    }
    
    // Initialize every equipment to nullptr
    body_armor_ = nullptr;
    player_stats_ = nullptr;
    helmet_ = nullptr;
    amulet_ = nullptr;
    left_arm_ = nullptr;
    right_arm_ = nullptr;
    gauntlets_ = nullptr;
    pants_ = nullptr;
    ring_1_ = nullptr;
    ring_2_ = nullptr;
    boots_ = nullptr;

}
