#include "tile.hpp"

#include "game_constants.hpp"

Tile::Tile(libpmg::Tile *other) :
libpmg::Tile(other->GetX(), other->GetY(), other->GetTagList()) {
    this->is_path_explored_ = other->is_path_explored_;
    this->path_cost_ = other->path_cost_;
    
    is_explored_ = false;
    is_highlighted_ = false;
    is_crosshair_ = false;
}

void Tile::Draw(TCODConsole &console, bool is_in_fov) {
    // Draw the char
    if (is_in_fov || is_explored_)
        console.setChar(GetX(), GetY(), GetChar());
    
    // Get the default bg and fg values
    auto bg {console.getCharBackground(GetX(), GetY())};
    auto fg {console.getCharForeground(GetX(), GetY())};
    
    // Draw explored tiles out of fov
    if (!is_in_fov && is_explored_) {
        bg.scaleHSV(1.0f, 0.4f);
        fg.scaleHSV(1.0f, 0.4f);
    }
    
    // Setup highlight if necessary
    if (is_highlighted_) {
        bg = TCODColor::lerp(bg, TCODColor::yellow, 0.25f);
        fg = TCODColor::lerp(fg, TCODColor::yellow, 1.0f);

        is_highlighted_ = false;
    }
    
    // Set the resulting color
    console.setCharBackground(GetX(), GetY(), bg);
    console.setCharForeground(GetX(), GetY(), fg);
    
    // Override default settings with crosshair if necessary
    if (is_crosshair_) {
        console.setChar(GetX(), GetY(), kCharCrosshair);
        console.setCharForeground(GetX(), GetY(), kCrosshairColor);
        
        is_crosshair_ = false;
    }
}
