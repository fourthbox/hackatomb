#ifndef PATH_FINDER_HPP_
#define PATH_FINDER_HPP_

#include "initiable_object.hpp"
#include "libtcod.hpp"
#include "maps_manager.hpp"

class TCODPathCallback : public ITCODPathCallback {
    public :
    float getWalkCost(int from_x, int from_y, int to_x, int to_y, void *user_data ) const override {
        assert(user_data != nullptr);
        auto map {static_cast<Map*> (user_data)};
        
        if (map->IsWall(to_x, to_y))
            return 0.0f;
        
        return 1.0f;
    }
};

class PathFinder : public InitiableObject {
public:
    void Initialize(MapsManager &map);
    bool Walk(size_t &out_x, size_t &out_y, size_t from_x, size_t from_y, size_t to_x, size_t to_y, size_t steps = 1);
    
private:
    std::unique_ptr<TCODPathCallback> path_callback_;
    std::unique_ptr<TCODPath> current_path_;

    bool ComputePath(size_t from_x, size_t from_y, size_t to_x, size_t to_y);
};

#endif /* PATH_FINDER_HPP_ */
