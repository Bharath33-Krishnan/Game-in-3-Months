#pragma once
#include "Collider.hpp"
#include "data_types.hpp"
#include "raylib/raylib.h"
#include "../entity.hpp"
#include "../PhysicsEngine.hpp"

namespace Core {

class CircleCollider2D :public Collider {
public:
    transform& base_t;
    float rad;

    //********* Override Solver ***********
    bool SolveCollision(Collider* other) override;

    //********* Constructors ***********
    inline CircleCollider2D(transform& base_t , float rad):base_t(base_t) {
        PhysicsEngine::registerCollider(this);
        this->collider_type = ColliderType::CIRCLE_2D;
        this->rad = rad;
    }
    inline CircleCollider2D(transform& base_t, float rad, bool isTrigger):base_t(base_t) {
        PhysicsEngine::registerCollider(this);
        this->collider_type = ColliderType::CIRCLE_2D;
        this->rad = rad;
        this->isTrigger = isTrigger;
    }
    inline CircleCollider2D(transform& base_t , float rad, bool isTrigger,
                            bool isCollidable):base_t(base_t) {
        PhysicsEngine::registerCollider(this);
        this->collider_type = ColliderType::CIRCLE_2D;
        this->rad = rad;
        this->isTrigger = isTrigger;
        this->isCollidable = isCollidable;
    }

    inline void drawCollider() override{
        DrawCircleLines(base_t.pos.x,base_t.pos.y , rad,GREEN);
    }

    inline vec2 getParameter(ColParams param) override{
        switch(param){
            case ColParams::POS:
                return base_t.pos; 
            case ColParams::ROT:
                return base_t.rot;
            case ColParams::SCALE:
                return base_t.scale * (rad);
            default:
                return vec2(-1);
        }
    }


    ~CircleCollider2D(){
    }
};

}; 
