#include "world.hpp"

#include "engine.hpp"
#include "game_constants.hpp"

World::World(std::shared_ptr<libpmg::WorldMap> map) :
libpmg::WorldMap {map},
TCODMap {(int)configs_->map_width_, (int)configs_->map_height_}
{}

void World::Draw() {
    for (size_t x {0}; x < getWidth(); x++) {
        for (size_t y {0}; y < getHeight(); y++) {
            auto tile = std::static_pointer_cast<libpmg::WorldTile>(GetTile(x, y));
            float value = tile->GetAltitude();
            
            if (value <= 0.1 )
                TCODConsole::root->setCharBackground(x, y, TCODColor::darkestAzure);
            else if (value < 0.2)
                TCODConsole::root->setCharBackground(x, y, TCODColor::darkerAzure);
            else if (value < 0.3)
                TCODConsole::root->setCharBackground(x, y, TCODColor::darkAzure);
            else if (value < 0.4)
                TCODConsole::root->setCharBackground(x, y, TCODColor::darkChartreuse);
            else if (value < 0.5)
                TCODConsole::root->setCharBackground(x, y, TCODColor::darkerChartreuse);
            else if (value < 0.6)
                TCODConsole::root->setCharBackground(x, y, TCODColor::darkestChartreuse);
            else if (value < 0.7)
                TCODConsole::root->setCharBackground(x, y, TCODColor::darkSepia);
            else if (value < 0.8)
                TCODConsole::root->setCharBackground(x, y, TCODColor::lightGrey);
            else if (value < 0.9)
                TCODConsole::root->setCharBackground(x, y, TCODColor::lighterGrey);
            else if (value >= 0.9)
                TCODConsole::root->setCharBackground(x, y, TCODColor::white);
        }
    }
}
