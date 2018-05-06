#ifndef PATH_FINDER_HPP_
#define PATH_FINDER_HPP_

#include "initiable_object.hpp"
#include "libtcod.hpp"
#include "maps_manager.hpp"

class PathFinder : public InitiableObject {
public:
    void Initialize(MapsManager &map);
    bool Walk(size_t &out_x, size_t &out_y, size_t from_x, size_t from_y, size_t to_x, size_t to_y, size_t steps = 1);
    
private:
    std::unique_ptr<TCODPath> current_path_;

    bool ComputePath(size_t from_x, size_t from_y, size_t to_x, size_t to_y);
};

#endif /* PATH_FINDER_HPP_ */
