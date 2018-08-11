#ifndef UI_INVENTORY_HPP_
#define UI_INVENTORY_HPP_

#include "ui_window.hpp"

#include "inventory_manager.hpp"
#include "map.hpp"

class UiInventory : public UiWindow {
public:
    void Initialize(InventoryManager &inventory_manager,
                    size_t width,
                    size_t height,
                    std::string const &name = "",
                    std::initializer_list<UiLabel_sp> labels = {});
    
    void Draw() override;
    
private:
    InventoryManager *inventory_manager_;
    std::unique_ptr<UiWindow> body_armor_frame_, item_list_frame_, player_stats_frame_, item_stats_frame_,
        helmet_frame_, amulet_frame_, left_arm_frame_, right_arm_frame_, torso_frame_, gauntlets_frame_, pants_frame_,
        ring_1_frame_, ring_2_frame_, boots_frame_;
};

#endif /* UI_INVENTORY_HPP_ */
