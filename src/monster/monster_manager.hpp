#ifndef MONSTER_MANAGER_HPP_
#define MONSTER_MANAGER_HPP_

#include "monster_factory.hpp"

class MonsterManager : public InitiableObject {
public:
    void Initialize(ActionManager &action_manager, ActorManager &actor_manager, MapsManager &maps_manager);
    void Draw(TCODConsole &console);
    void SetPermaVisible(bool is_perma_visible, Monster *monster = nullptr) const;
    void Update(size_t speed) const;
    Monster *GetMonsterByCoordinates(size_t x, size_t y) const;

private:
    ActionManager *action_manager_;
    MapsManager *maps_manager_;
    
    MonsterFactory monster_factory_;
    std::vector<std::unique_ptr<Monster>> monster_list_;
};

#endif /* MONSTER_MANAGER_HPP_ */
