#ifndef ITEMS_MANAGER_HPP_
#define ITEMS_MANAGER_HPP_

#include <array>

#include "item.hpp"

static const int kInventorySize = 10;

class ItemsManager {
public:
    ItemsManager();
    
    inline Item* GetHelmet() { return helmet_.get(); }
    inline Item* GetAmulet() { return amulet_.get(); }
    inline Item* GetLeftArm() { return left_arm_.get(); }
    inline Item* GetRightArm() { return right_arm_.get(); }
    inline Item* GetBodyArmor() { return body_armor_.get(); }
    inline Item* GetGauntlets() { return gauntlets_.get(); }
    inline Item* GetPants() { return pants_.get(); }
    inline Item* GetRing1() { return ring_1_.get(); }
    inline Item* GetRing2() { return ring_2_.get(); }
    inline Item* GetBoots() { return boots_.get(); }
    
    inline Item* GetItemBySlot(size_t slot) { assert(slot <= kInventorySize); return inventory_slots_[slot].get(); }
    
private:
    std::array<Item_up, kInventorySize> inventory_slots_; /**< This is the actual inventory*/
    // Those are the equipped items
    Item_up body_armor_, player_stats_, helmet_, amulet_, left_arm_, right_arm_, gauntlets_, pants_, ring_1_, ring_2_, boots_;

};

#endif /* ITEMS_MANAGER_HPP_ */
