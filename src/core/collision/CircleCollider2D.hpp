#pragma once
#include "Collider.hpp"
#include "data_types.hpp"
#include "raylib/raylib.h"
#include "../entity.hpp"

namespace Core {

class CircleCollider2D :public Collider {
private:
    transform& base_t;
    // vec2* center;
    float rad;

protected:
    //********* Override Solver ***********
    bool SolveCollision(Collider &other) override;

public:
    //********* Constructors ***********
    inline CircleCollider2D(transform& base_t , float rad):base_t(base_t) {
        this->collider_type = ColliderType::CIRCLE_2D;
        // this->base_t = base_t;
        this->rad = rad;
    }
    inline CircleCollider2D(transform& base_t, float rad, bool isTrigger):base_t(base_t) {
        this->collider_type = ColliderType::CIRCLE_2D;
        this->rad = rad;
        this->isTrigger = isTrigger;
    }
    inline CircleCollider2D(transform& base_t , float rad, bool isTrigger,
                            bool isCollidable):base_t(base_t) {
        this->collider_type = ColliderType::CIRCLE_2D;
        this->rad = rad;
        this->isTrigger = isTrigger;
        this->isCollidable = isCollidable;
    }

    inline void drawCollider() override{
        DrawCircleLines(base_t.pos.x,base_t.pos.y , rad,GREEN);
    }

    ~CircleCollider2D(){
    }
};

}; 
