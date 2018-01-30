#ifndef ROOT_CONSOLE_MANAGER_HPP_
#define ROOT_CONSOLE_MANAGER_HPP_

#include <string>

#include "libtcod.hpp"

class RootConsoleManager {
public:
    RootConsoleManager();
    void Initialize(size_t width, size_t height,
                    size_t left_offset, size_t right_offset,
                    size_t top_offset, size_t bottom_offset,
                    std::string root_name);
    void SetChar(size_t x, size_t y, int sprite, TCODColor color);
    void SetBackground(size_t x, size_t y, TCODColor color);
    void Clear();
    void Render();
    
private:
    bool initialized_;
    size_t width_, height_, left_offset_, right_offset_, top_offset_, bottom_offset_;
    
    void MapCharacters();
};

#endif /* ROOT_CONSOLE_MANAGER_HPP_ */
