#include "tile.hpp"

Tile::Tile(libpmg::Tile *other) :
libpmg::Tile(other->GetX(), other->GetY(), other->GetTagList()) {
    this->is_path_explored_ = other->is_path_explored_;
    this->path_cost_ = other->path_cost_;
    
    explored_ = false;
}

void Tile::Draw(TCODConsole *console, bool is_in_fov) {
    if (is_in_fov || explored_)
        console->setChar(GetX(), GetY(), GetChar());
    
    if (!is_in_fov && explored_) {
        auto bg {console->getCharBackground(GetX(), GetY())};
        auto fg {console->getCharForeground(GetX(), GetY())};

        bg.scaleHSV(1.0f, 0.4f);
        fg.scaleHSV(1.0f, 0.4f);
        
        console->setCharBackground(GetX(), GetY(), bg);
        console->setCharForeground(GetX(), GetY(), fg);
    }
}
