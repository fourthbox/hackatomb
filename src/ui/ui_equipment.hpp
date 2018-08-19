#ifndef UI_EQUIPMENT_HPP_
#define UI_EQUIPMENT_HPP_

#include "ui_window.hpp"

#include "items_manager.hpp"
#include "map.hpp"

class UiEquipment : public UiWindow {
public:
    void Initialize(ItemsManager &items_manager,
                    size_t width,
                    size_t height,
                    std::string const &name = "",
                    std::initializer_list<UiLabel_sp> labels = {});
    
    void Draw() override;
    
private:
    ItemsManager *items_manager_;
    std::unique_ptr<UiWindow> body_armor_frame_, item_list_frame_, player_stats_frame_, item_stats_frame_,
    helmet_frame_, amulet_frame_, left_arm_frame_, right_arm_frame_, torso_frame_, gauntlets_frame_, pants_frame_,
    ring_1_frame_, ring_2_frame_, boots_frame_;
};

#endif /* UI_EQUIPMENT_HPP_ */
