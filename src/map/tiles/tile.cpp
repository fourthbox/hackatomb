#include "tile.hpp"

Tile::Tile(libpmg::Tile *other) :
libpmg::Tile(other->GetX(), other->GetY(), other->GetTagList()) {
    this->is_path_explored_ = other->is_path_explored_;
    this->path_cost_ = other->path_cost_;
    
    is_explored_ = false;
    is_highlighted_ = false;
}

void Tile::Draw(TCODConsole &console, bool is_in_fov) {
    if (is_in_fov || is_explored_)
        console.setChar(GetX(), GetY(), GetChar());
    
    auto bg {console.getCharBackground(GetX(), GetY())};
    auto fg {console.getCharForeground(GetX(), GetY())};
    
    if (!is_in_fov && is_explored_) {
        bg.scaleHSV(1.0f, 0.4f);
        fg.scaleHSV(1.0f, 0.4f);
    }
    
    if (is_highlighted_) {
        bg = bg + TCODColor::yellow;
        fg = fg + TCODColor::yellow;
        
        is_highlighted_ = false;
    }
    
    console.setCharBackground(GetX(), GetY(), bg);
    console.setCharForeground(GetX(), GetY(), fg);
}
