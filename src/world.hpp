#ifndef WORLD_HPP_
#define WORLD_HPP_

#include "libpmg.hpp"
#include "libtcod.hpp"

class World : public libpmg::WorldMap, public TCODMap {
public:
    World(std::shared_ptr<libpmg::WorldMap> map);
    
    void Draw();
    
};

#endif /* WORLD_HPP_ */
