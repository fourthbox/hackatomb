#include "tile.hpp"

Tile::Tile(std::shared_ptr<libpmg::Tile> other) :
    libpmg::Tile(other->GetX(), other->GetY(), other->GetTagList()) {
    this->is_explored_ = other->is_explored_;
    this->cost_ = other->cost_;
}
