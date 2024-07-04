#pragma once
#include "Collider.hpp"
#include "CircleCollider2D.hpp"
#include "../../utilities/data_types.hpp"
#include "raylib/raylib.h"
#include "../entity.hpp"
#include "../PhysicsEngine.hpp"

namespace Core{

class BoxCollider2D:public Collider{
private:
    bool SolveWithBoxCollider(BoxCollider2D* other,i32 id,f32 phy_delta);
    bool SolveWithCircleCollider(CircleCollider2D* other,i32 id,f32 phy_delta);
public:
    transform& base_t;
    vec2 diagonal;

    //********* Override Solver ***********
    bool SolveCollision(Collider* other,f32 phy_delta) override;

    //********* Constructors ***********
    inline BoxCollider2D(transform& base_t,vec2 diagonal):base_t(base_t){
        PhysicsEngine::registerCollider(this);
        this->collider_type = ColliderType::BOX_2D;
        this->diagonal = diagonal;
        this->Offset = 0.5*diagonal;
    }
    inline BoxCollider2D(transform& base_t,vec2 diagonal, bool isStationary):base_t(base_t){
        PhysicsEngine::registerCollider(this);
        this->collider_type = ColliderType::BOX_2D;
        this->diagonal = diagonal;
        this->isStationary = isStationary;
        this->Offset = 0.5*diagonal;
    }
    inline BoxCollider2D(transform& base_t,vec2 diagonal,bool isStationary,bool isTrigger):base_t(base_t){
        PhysicsEngine::registerCollider(this);
        this->collider_type = ColliderType::BOX_2D;
        this->diagonal = diagonal;
        this->isTrigger = isTrigger;
        this->isStationary = isStationary;
        this->Offset = 0.5*diagonal;
    }

    inline void drawCollider() override{
        vec2 pos = getParameter(ColParams::POS) - .5*diagonal;
        vec2 diagonal = getParameter(ColParams::SCALE);
        DrawRectangleLines(pos.x,pos.y , 2.*diagonal.x, 2.*diagonal.y,GREEN);
    }
    
    inline vec2 getParameter(ColParams param) override{
        switch(param){
            case ColParams::POS:
                return base_t.pos - Offset + .5*diagonal;
            case ColParams::ROT:
                return base_t.rot;
            case ColParams::SCALE:
                return (.5 * diagonal);
            default:
                return vec2(-1);
        }
    }

    ~BoxCollider2D(){
    }
};

};




