#include "ui_inventory.hpp"

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
static const size_t kHelmetPieceHeight = 10;
static const size_t kTorsoPieceWidth = 20;
static const size_t kTorsoPieceHeight = 20;
static const size_t kArmPieceWidth = 9;
static const size_t kArmPieceHeight = 22;
static const size_t kPantsPieceWidth = 16;
static const size_t kPantsPieceHeight = 18;

void UiInventory::Initialize(size_t width, size_t height, std::string const &name, std::initializer_list<UiLabel_sp> labels) {
    assert(!initialized_);

    UiWindow::Initialize(width, height, name, labels);
    
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

    // Body armor pieces
    helmet_piece_ = std::make_unique<UiWindow>();
    amulet_piece_ = std::make_unique<UiWindow>();
    left_arm_piece_ = std::make_unique<UiWindow>();
    right_arm_piece_ = std::make_unique<UiWindow>();
    torso_piece_ = std::make_unique<UiWindow>();
    gaunlet_piece_ = std::make_unique<UiWindow>();
    pants_piece_ = std::make_unique<UiWindow>();
    ring_1_piece_ = std::make_unique<UiWindow>();
    ring_2_piece_ = std::make_unique<UiWindow>();
    
    helmet_piece_->Initialize(kHelmetPieceWidth,
                              kHelmetPieceHeight);
    amulet_piece_->Initialize(kTrinketPieceWidth,
                              kTrinketPieceHeight);
    left_arm_piece_->Initialize(kArmPieceWidth,
                                kArmPieceHeight);
    right_arm_piece_->Initialize(kArmPieceWidth,
                                 kArmPieceHeight);
    torso_piece_->Initialize(kTorsoPieceWidth,
                             kTorsoPieceHeight);
    gaunlet_piece_->Initialize(kTrinketPieceWidth,
                               kTrinketPieceHeight);
    pants_piece_->Initialize(kPantsPieceWidth,
                             kPantsPieceHeight);
    ring_1_piece_->Initialize(kTrinketPieceWidth,
                              kTrinketPieceHeight);
    ring_2_piece_->Initialize(kTrinketPieceWidth,
                              kTrinketPieceHeight);
}

void UiInventory::Draw() {
    assert(initialized_);
    
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
    helmet_piece_->Draw();
    amulet_piece_->Draw();
    left_arm_piece_->Draw();
    right_arm_piece_->Draw();
    torso_piece_->Draw();
    gaunlet_piece_->Draw();
    pants_piece_->Draw();
    ring_1_piece_->Draw();
    ring_2_piece_->Draw();
    
    TCODConsole::blit(helmet_piece_->GetConsole(), 0, 0, 0, 0,
                      console_.get(), 18, 3);
    TCODConsole::blit(left_arm_piece_->GetConsole(), 0, 0, 0, 0,
                      console_.get(), 3, 15);
    TCODConsole::blit(torso_piece_->GetConsole(), 0, 0, 0, 0,
                      console_.get(), 14, 14);
    TCODConsole::blit(right_arm_piece_->GetConsole(), 0, 0, 0, 0,
                      console_.get(), 36, 15);
    TCODConsole::blit(pants_piece_->GetConsole(), 0, 0, 0, 0,
                      console_.get(), 16, 35);
    TCODConsole::blit(amulet_piece_->GetConsole(), 0, 0, 0, 0,
                      console_.get(), 3, 5);
    TCODConsole::blit(gaunlet_piece_->GetConsole(), 0, 0, 0, 0,
                      console_.get(), 3, 38);
    TCODConsole::blit(ring_1_piece_->GetConsole(), 0, 0, 0, 0,
                      console_.get(), 36, 38);
    TCODConsole::blit(ring_2_piece_->GetConsole(), 0, 0, 0, 0,
                      console_.get(), 36, 45);
}
