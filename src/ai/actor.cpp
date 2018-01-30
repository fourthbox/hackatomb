#include "actor.hpp"

#include <cassert>

#include "engine.hpp"
#include "game_utils.hpp"

using std::string;

Actor::Actor(size_t x, size_t y, int ch, string &name, const TCODColor &col, Stats &stats) :
    x_ {x},
    y_ {y},
    sprite_ {ch},
    name_ {name},
    color_ {col},
    stats_ {stats}
{}

void Actor::InitializeAi(Ai_p ai) {
    assert(ai != nullptr);
    
    ai_ = ai;
    ai_->Initialize(shared_from_this());
}

void Actor::Draw() {
    Engine::GetInstance().GetRootConsoleManager().SetChar(x_, y_, sprite_, color_);
}

void Actor::Update() {
    assert(ai_ != nullptr);
    
    ai_->Update();
}

void Actor::SetPosition(size_t x, size_t y) {
    x_ = x;
    y_ = y;
}

libpmg::Location Actor::GetPosition() {
    return libpmg::Location(x_, y_);
}

bool Actor::Interact(Actor_p owner) {
    assert(ai_ != nullptr);
    
    return ai_->Interact(owner);
}

size_t Actor::GetAtk() {
    return stats_.atk_;
}

size_t Actor::GetDef() {
    return stats_.def_;
}

void Actor::ApplyDmg(size_t dmg) {
    stats_.current_hp_ -= dmg;
    
    if (stats_.current_hp_ <= 0)
        Die();
}

void Actor::Die() {
    sprite_ = '%';
    color_ = TCODColor::darkRed;
}
