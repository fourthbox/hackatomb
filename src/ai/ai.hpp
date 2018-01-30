#ifndef AI_HPP_
#define AI_HPP_

#include <memory>

class Actor;

class Ai {
public :
    void Initialize(std::shared_ptr<Actor> owner);
    
    virtual void Update() = 0;
    virtual bool Interact(std::shared_ptr<Actor> other) = 0;
    
protected:
    std::shared_ptr<Actor> actor_;
};

class PlayerAi : public Ai {
public :
    void Update();
    bool Interact(std::shared_ptr<Actor> other);
    
private :
    bool MoveOrInteract(int x, int y);
};

class MonsterAi : public Ai {
public :
    void Update();
    bool Interact(std::shared_ptr<Actor> other);
    
private :
    bool MoveOrInteract(int x, int y);
};

typedef std::shared_ptr<Ai> Ai_p;

#endif /* AI_HPP_ */
