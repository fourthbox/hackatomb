#include "ui_equipment.hpp"

static const size_t kBodyArmorFrameWidth = 46;
static const size_t kBodyArmorFrameHeight = 54;
static const size_t kItemListFrameWidth = 60;
static const size_t kItemListFrameHeight = 34;
static const size_t kPlayerStatsFrameWidth = 26;
static const size_t kPlayerStatsFrameHeight = 34;
static const size_t kItemStatsFrameWidth = 86;
static const size_t kItemStatsFrameHeight = 20;

static const size_t kTrinketPieceWidth = 9;
static const size_t kTrinketPieceHeight = 6;
static const size_t kHelmetPieceWidth = 12;
static const size_t kHelmetPieceHeight = 8;
static const size_t kTorsoPieceWidth = 20;
static const size_t kTorsoPieceHeight = 18;
static const size_t kArmPieceWidth = 9;
static const size_t kArmPieceHeight = 22;
static const size_t kPantsPieceWidth = 16;
static const size_t kPantsPieceHeight = 16;
static const size_t kBootsPieceWidth = 16;
static const size_t kBootsPieceHeight = 6;

void UiEquipment::Initialize(ItemsManager &items_manager, size_t width, size_t height, std::string const &name, std::initializer_list<UiLabel_sp> labels) {
    assert(!initialized_);

    UiWindow::Initialize(width, height, name, labels);
    
    items_manager_ = &items_manager;
    
    // Window Frames
    body_armor_frame_ = std::make_unique<UiWindow>();
    item_list_frame_ = std::make_unique<UiWindow>();
    player_stats_frame_ = std::make_unique<UiWindow>();
    item_stats_frame_ = std::make_unique<UiWindow>();
    
    body_armor_frame_->Initialize(kBodyArmorFrameWidth,
                                  kBodyArmorFrameHeight);
    item_list_frame_->Initialize(kItemListFrameWidth,
                                 kItemListFrameHeight);
    player_stats_frame_->Initialize(kPlayerStatsFrameWidth,
                                    kPlayerStatsFrameHeight);
    item_stats_frame_->Initialize(kItemStatsFrameWidth,
                                  kItemStatsFrameHeight);

    // Initialize equipment slots
    helmet_frame_ = std::make_unique<UiWindow>();
    amulet_frame_ = std::make_unique<UiWindow>();
    left_arm_frame_ = std::make_unique<UiWindow>();
    right_arm_frame_ = std::make_unique<UiWindow>();
    torso_frame_ = std::make_unique<UiWindow>();
    gauntlets_frame_ = std::make_unique<UiWindow>();
    pants_frame_ = std::make_unique<UiWindow>();
    ring_1_frame_ = std::make_unique<UiWindow>();
    ring_2_frame_ = std::make_unique<UiWindow>();
    boots_frame_ = std::make_unique<UiWindow>();
    
    // Initialize equipment strings
    auto helmet_label {std::make_shared<UiCenteredLabel>(kHelmetPieceWidth,
                                                         kHelmetPieceHeight,
                                                         items_manager_->GetHelmet()->GetShortDescription())};
    auto amulet_label {std::make_shared<UiCenteredLabel>(kTrinketPieceWidth,
                                                         kTrinketPieceHeight,
                                                         items_manager_->GetAmulet()->GetShortDescription())};
    auto left_arm_label {std::make_shared<UiCenteredLabel>(kArmPieceWidth,
                                                           kArmPieceHeight,
                                                           items_manager_->GetLeftArm()->GetShortDescription())};
    auto right_arm_label {std::make_shared<UiCenteredLabel>(kArmPieceWidth,
                                                            kArmPieceHeight,
                                                            items_manager_->GetRightArm()->GetShortDescription())};
    auto torso_label {std::make_shared<UiCenteredLabel>(kTorsoPieceWidth,
                                                        kTorsoPieceHeight,
                                                        items_manager_->GetBodyArmor()->GetShortDescription())};
    auto gauntlets_label {std::make_shared<UiCenteredLabel>(kTrinketPieceWidth,
                                                            kTrinketPieceHeight,
                                                            items_manager_->GetGauntlets()->GetShortDescription())};
    auto pants_label {std::make_shared<UiCenteredLabel>(kPantsPieceWidth,
                                                        kPantsPieceHeight,
                                                        items_manager_->GetPants()->GetShortDescription())};
    auto ring_1_label {std::make_shared<UiCenteredLabel>(kTrinketPieceWidth,
                                                         kTrinketPieceHeight,
                                                         items_manager_->GetRing1()->GetShortDescription())};
    auto ring_2_label {std::make_shared<UiCenteredLabel>(kTrinketPieceWidth,
                                                         kTrinketPieceHeight,
                                                         items_manager_->GetRing2()->GetShortDescription())};
    auto boots_label {std::make_shared<UiCenteredLabel>(kBootsPieceWidth,
                                                        kBootsPieceHeight,
                                                        items_manager_->GetBoots()->GetShortDescription())};

    helmet_frame_->Initialize(kHelmetPieceWidth, kHelmetPieceHeight, "", {helmet_label});
    amulet_frame_->Initialize(kTrinketPieceWidth, kTrinketPieceHeight, "", {amulet_label});
    left_arm_frame_->Initialize(kArmPieceWidth, kArmPieceHeight, "", {left_arm_label});
    right_arm_frame_->Initialize(kArmPieceWidth, kArmPieceHeight, "", {right_arm_label});
    torso_frame_->Initialize(kTorsoPieceWidth, kTorsoPieceHeight, "", {torso_label});
    gauntlets_frame_->Initialize(kTrinketPieceWidth, kTrinketPieceHeight, "", {gauntlets_label});
    pants_frame_->Initialize(kPantsPieceWidth, kPantsPieceHeight, "", {pants_label});
    ring_1_frame_->Initialize(kTrinketPieceWidth, kTrinketPieceHeight, "", {ring_1_label});
    ring_2_frame_->Initialize(kTrinketPieceWidth, kTrinketPieceHeight, "", {ring_2_label});
    boots_frame_->Initialize(kBootsPieceWidth, kBootsPieceHeight, "", {boots_label});
    
    // Initialize the inventory slots
    std::string alphabet {"abcdefghijklmnopqrstuvwxyz"};
    assert(kInventorySize <= alphabet.size());
    alphabet.resize(kInventorySize);
    
    auto base_x {6}, base_y {2};
    for (auto const &c : alphabet) {
        auto label {std::make_shared<UiLabelWithHandler>(base_x, base_y, c, "stocazzo")};
    }
}

void UiEquipment::Draw() {
    assert(initialized_);
    
    // Update equipment labels
    helmet_frame_->UpdateLabelById("", items_manager_->GetHelmet()->GetShortDescription());
    amulet_frame_->UpdateLabelById("", items_manager_->GetAmulet()->GetShortDescription());
    left_arm_frame_->UpdateLabelById("", items_manager_->GetLeftArm()->GetShortDescription());
    right_arm_frame_->UpdateLabelById("", items_manager_->GetRightArm()->GetShortDescription());
    torso_frame_->UpdateLabelById("", items_manager_->GetBodyArmor()->GetShortDescription());
    gauntlets_frame_->UpdateLabelById("", items_manager_->GetGauntlets()->GetShortDescription());
    pants_frame_->UpdateLabelById("", items_manager_->GetPants()->GetShortDescription());
    ring_1_frame_->UpdateLabelById("", items_manager_->GetRing1()->GetShortDescription());
    ring_2_frame_->UpdateLabelById("", items_manager_->GetRing2()->GetShortDescription());
    boots_frame_->UpdateLabelById("", items_manager_->GetBoots()->GetShortDescription());
    
    UiWindow::Draw();
    
    // Draw frames
    body_armor_frame_->Draw();
    item_list_frame_->Draw();
    player_stats_frame_->Draw();
    item_stats_frame_->Draw();
    
    TCODConsole::blit(body_armor_frame_->GetConsole(), 0, 0, 0, 0,
                      console_.get(), 1, 1);
    TCODConsole::blit(item_list_frame_->GetConsole(), 0, 0, 0, 0,
                      console_.get(), kBodyArmorFrameWidth + 1, 1);
    TCODConsole::blit(player_stats_frame_->GetConsole(), 0, 0, 0, 0,
                      console_.get(), kBodyArmorFrameWidth + kItemListFrameWidth + 1, 1);
    TCODConsole::blit(item_stats_frame_->GetConsole(), 0, 0, 0, 0,
                      console_.get(), kBodyArmorFrameWidth + 1, kItemListFrameHeight + 1);
    
    // Draw body armor pieces
    helmet_frame_->Draw();
    amulet_frame_->Draw();
    left_arm_frame_->Draw();
    right_arm_frame_->Draw();
    torso_frame_->Draw();
    gauntlets_frame_->Draw();
    pants_frame_->Draw();
    ring_1_frame_->Draw();
    ring_2_frame_->Draw();
    boots_frame_->Draw();
    
    TCODConsole::blit(helmet_frame_->GetConsole(), 0, 0, 0, 0,
                      console_.get(), 18, 3);
    TCODConsole::blit(left_arm_frame_->GetConsole(), 0, 0, 0, 0,
                      console_.get(), 3, 13);
    TCODConsole::blit(torso_frame_->GetConsole(), 0, 0, 0, 0,
                      console_.get(), 14, 12);
    TCODConsole::blit(right_arm_frame_->GetConsole(), 0, 0, 0, 0,
                      console_.get(), 36, 13);
    TCODConsole::blit(pants_frame_->GetConsole(), 0, 0, 0, 0,
                      console_.get(), 16, 31);
    TCODConsole::blit(amulet_frame_->GetConsole(), 0, 0, 0, 0,
                      console_.get(), 3, 5);
    TCODConsole::blit(gauntlets_frame_->GetConsole(), 0, 0, 0, 0,
                      console_.get(), 3, 38);
    TCODConsole::blit(ring_1_frame_->GetConsole(), 0, 0, 0, 0,
                      console_.get(), 36, 38);
    TCODConsole::blit(ring_2_frame_->GetConsole(), 0, 0, 0, 0,
                      console_.get(), 36, 45);
    TCODConsole::blit(boots_frame_->GetConsole(), 0, 0, 0, 0,
                      console_.get(), 16, 48);
}
