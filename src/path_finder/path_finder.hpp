#ifndef PATH_FINDER_HPP_
#define PATH_FINDER_HPP_

#include "initiable_object.hpp"
#include "libtcod.hpp"
#include "map.hpp"

class PathFinder : public InitiableObject {
public:
    PathFinder();
    void Initialize(Map_p map);
    Coordinate_p Walk(size_t from_x, size_t from_y, size_t to_x, size_t to_y, size_t steps = 1);
    
private:
    std::shared_ptr<TCODPath> current_path_;

    void SetMap(Map_p map);
    bool ComputePath(size_t from_x, size_t from_y, size_t to_x, size_t to_y);
};

#endif /* PATH_FINDER_HPP_ */
