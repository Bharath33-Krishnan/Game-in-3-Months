#pragma once
#include "Collider.hpp"
#include "data_types.hpp"
#include "raylib/raylib.h"
#include "../entity.hpp"

namespace Core{

class BoxCollider2D:public Collider{
private:
    transform& base_t;
    vec2 diagonal;
protected:
    //********* Override Solver ***********
    bool SolveCollision(Collider& other) override;

public:
    //********* Constructors ***********
    inline BoxCollider2D(transform& base_t,vec2 diagonal):base_t(base_t)
    {
        this->collider_type = ColliderType::BOX_2D;
        this->diagonal = diagonal;
    }
    inline BoxCollider2D(transform& base_t,vec2 diagonal, bool isTrigger):base_t(base_t){
        this->collider_type = ColliderType::BOX_2D;
        this->diagonal = diagonal;
        this->isTrigger = isTrigger;
    }
    inline BoxCollider2D(transform& base_t,vec2 diagonal, bool isTrigger, bool isCollidable):base_t(base_t){
        this->collider_type = ColliderType::BOX_2D;
        this->diagonal = diagonal;
        this->isTrigger = isTrigger;
        this->isCollidable = isCollidable;
    }

    inline void drawCollider() override{
        DrawRectangleLines(base_t.pos.x,base_t.pos.y , diagonal.x, diagonal.y,GREEN);
    }

    ~BoxCollider2D(){
    }
};

};




