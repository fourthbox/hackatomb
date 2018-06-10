#ifndef MONSTER_MANAGER_HPP_
#define MONSTER_MANAGER_HPP_

#include "monster_factory.hpp"

class Player;

class MonsterManager : public InitiableObject {
public:
    void Initialize(ActionManager &action_manager, ActorManager &actor_manager, MapsManager &maps_manager);
    void Draw(TCODConsole &console, Player const &player);
    void SetPermaVisible(bool is_perma_visible, Monster *monster = nullptr) const;
    void Update(size_t speed, ActionManager &action_manager, MapsManager &maps_manager) const;
    Monster *GetMonsterByCoordinates(size_t x, size_t y) const;
    std::vector<Actor*> GetMonsterList() const;

private:
    ActionManager *action_manager_;
    MapsManager *maps_manager_;
    
    MonsterFactory monster_factory_;
    std::vector<std::unique_ptr<Monster>> monster_list_;
};

#endif /* MONSTER_MANAGER_HPP_ */
