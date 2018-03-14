#ifndef ACTOR_HPP_
#define ACTOR_HPP_

#include <string>

#include "ai.hpp"
#include "console_proxy.hpp"
#include "game_globals.hpp"
#include "libtcod.hpp"
#include "map_builder.hpp"
#include "stats.hpp"

using std::string;

class Actor : public std::enable_shared_from_this<Actor> {
public:
    Actor(size_t x, size_t y, int ch, string &name, const TCODColor &col, Stats &stats);
    void InitializeAi(Ai_p ai);
    
    void Update();
    void Draw(ConsoleProxy &console);
    
    bool Interact(std::shared_ptr<Actor> owner);
    
    // Getters and setters
    void SetPosition(size_t x, size_t y);
    libpmg::Location GetPosition();
    libpmg::Location GetPositionWithOffset();
    size_t GetAtk();
    size_t GetDef();
    void ApplyDmg(size_t dmg);
    void Die();
    
protected:    
    // Base info
    size_t x_, y_;
    int sprite_;
    TCODColor color_;
    string name_;
    Stats stats_;

    Ai_p ai_;
};

typedef std::shared_ptr<Actor> Actor_p;

#endif /* ACTOR_HPP_ */
