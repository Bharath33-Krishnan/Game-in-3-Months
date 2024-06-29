#pragma once
#include "Collider.hpp"
#include "CircleCollider2D.hpp"
#include "data_types.hpp"
#include "raylib/raylib.h"
#include "../entity.hpp"
#include "../PhysicsEngine.hpp"

namespace Core{

class BoxCollider2D:public Collider{
private:
    bool SolveWithBoxCollider(BoxCollider2D* other,int id);
    bool SolveWithCircleCollider(CircleCollider2D* other,int id);
public:
    transform& base_t;
    vec2 diagonal;

    //********* Override Solver ***********
    bool SolveCollision(Collider* other) override;

    //********* Constructors ***********
    inline BoxCollider2D(transform& base_t,vec2 diagonal):base_t(base_t){
        PhysicsEngine::registerCollider(this);
        this->collider_type = ColliderType::BOX_2D;
        this->diagonal = diagonal;
    }
    inline BoxCollider2D(transform& base_t,vec2 diagonal, bool isTrigger):base_t(base_t){
        PhysicsEngine::registerCollider(this);
        this->collider_type = ColliderType::BOX_2D;
        this->diagonal = diagonal;
        this->isTrigger = isTrigger;
    }
    inline BoxCollider2D(transform& base_t,vec2 diagonal, bool isTrigger, bool isCollidable):base_t(base_t){
        PhysicsEngine::registerCollider(this);
        this->collider_type = ColliderType::BOX_2D;
        this->diagonal = diagonal;
        this->isTrigger = isTrigger;
        this->isCollidable = isCollidable;
    }

    inline void drawCollider() override{
        DrawRectangleLines(base_t.pos.x,base_t.pos.y , diagonal.x, diagonal.y,GREEN);
    }
    
    inline vec2 getParameter(ColParams param) override{
        switch(param){
            case ColParams::POS:
                return base_t.pos + base_t.scale * (.5 * diagonal);
            case ColParams::ROT:
                return base_t.rot;
            case ColParams::SCALE:
                return base_t.scale * (.5 * diagonal);
            default:
                return vec2(-1);
        }
    }

    ~BoxCollider2D(){
    }
};

};




