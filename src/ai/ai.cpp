#include "ai.hpp"

#include <cassert>

#include "actor.hpp"
#include "engine.hpp"
#include "key_mapper.hpp"

void Ai::Initialize(Actor_p owner) {
    assert(owner != nullptr);
    
    actor_ = owner;
}

void PlayerAi::Update() {
    assert(actor_ != nullptr);

    auto action { KeyMapper::GetActionByKey() };
    size_t x {0};
    size_t y {0};
        
    switch(action) {
        case KeyMapper::Action::MOVE_N:
            y--;
            break;

        case KeyMapper::Action::MOVE_NE:
            y--;
            x++;
            break;

        case KeyMapper::Action::MOVE_E:
            x++;
            break;

        case KeyMapper::Action::MOVE_SE:
            y++;
            x++;
            break;

        case KeyMapper::Action::MOVE_S:
            y++;
            break;

        case KeyMapper::Action::MOVE_SW:
            y++;
            x--;
            break;

        case KeyMapper::Action::MOVE_W:
            x--;
            break;

        case KeyMapper::Action::MOVE_NW:
            y--;
            x--;
            break;

        default:
            break;
    }
    
    if (x != 0 || y != 0) {
        Engine::GetInstance().PlayerPerformedAction();
        if (MoveOrInteract(actor_->GetPosition().GetX() + x, actor_->GetPosition().GetY() + y))
            Engine::GetInstance().ComputeFov();
    }
}

bool PlayerAi::MoveOrInteract(int x, int y) {
    assert(actor_ != nullptr);
    
    if (!Engine::GetInstance().CanMoveToPosition(x, y))
        return false;
    
    if (auto obstacle {Engine::GetInstance().GetActor(x, y)}; obstacle != nullptr) {
        obstacle->Interact(actor_);
        return false;
    }
    
    actor_->SetPosition(x, y);

    return true;
}

bool PlayerAi::Interact(Actor_p owner) {
    assert(actor_ != nullptr);

    return true;
}

void MonsterAi::Update() {
    assert(actor_ != nullptr);

}

bool MonsterAi::MoveOrInteract(int x, int y) {
    assert(actor_ != nullptr);
        
    return true;
}

bool MonsterAi::Interact(Actor_p other) {
    assert(actor_ != nullptr);

    if (other->GetAtk() > actor_->GetDef())
        actor_->ApplyDmg(other->GetAtk() - actor_->GetDef());
    
    return true;
}

