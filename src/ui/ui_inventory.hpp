#ifndef UI_INVENTORY_HPP_
#define UI_INVENTORY_HPP_

#include "ui_window.hpp"

#include "map.hpp"

class UiInventory : public UiWindow {
public:
    void Initialize(size_t width, size_t height, std::string const &name = "", std::initializer_list<UiLabel> labels = {}) override;
    
    void Draw() override;
    
private:
    std::unique_ptr<UiWindow> body_armor_frame_, item_list_frame_, player_stats_frame_, item_stats_frame_,
        helmet_piece_, amulet_piece_, left_arm_piece_, right_arm_piece_, torso_piece_, gaunlet_piece_, pants_piece_,
        ring_1_piece_, ring_2_piece_;
};

#endif /* UI_INVENTORY_HPP_ */
