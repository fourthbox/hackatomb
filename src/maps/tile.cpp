#include "tile.hpp"

Tile::Tile(std::shared_ptr<libpmg::Tile> other) :
libpmg::Tile(other->GetX(), other->GetY(), other->GetTagList()) {
    this->is_explored_ = other->is_explored_;
    this->cost_ = other->cost_;
    
    has_door_ = HasTag(libpmg::TagManager::GetInstance().door_tag_);
}

bool Tile::HasDoor() {
    return has_door_;
}

