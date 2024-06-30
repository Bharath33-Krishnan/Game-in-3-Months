#include "BoxCollider2D.hpp"
#include "raylib/raylib.h"
#include <algorithm>

bool Core::BoxCollider2D::SolveWithBoxCollider(Core::BoxCollider2D* other,i32 id,f32 phy_delta){
    vec2 pos = getParameter(ColParams::POS);
    Rectangle my_rec = {base_t.pos.x,base_t.pos.y,diagonal.x,diagonal.y};
    Rectangle other_rec = {other->base_t.pos.x,other->base_t.pos.y,other->diagonal.x,other->diagonal.y};

    if(CheckCollisionRecs(my_rec, other_rec)){
        if(this->isTrigger || other->isTrigger)
            return true;
        Rectangle overlap_rec = GetCollisionRec(my_rec, other_rec);
        f32 sep =  0.5 * std::min(overlap_rec.width,overlap_rec.height);
        vec2 sep_vec = sep * (this->base_t.pos - other->base_t.pos).normalize();
        if(!other->isStationary)
            other->base_t.pos = other->base_t.pos - sep_vec;
        if(!this->isStationary)
            this->base_t.pos = this->base_t.pos + sep_vec;
        return true;
    }
    return false;
}


bool Core::BoxCollider2D::SolveWithCircleCollider(Core::CircleCollider2D* other,i32 id,f32 phy_delta){
    bool return_value = false;
    Rectangle my_rec = {base_t.pos.x,base_t.pos.y,diagonal.x,diagonal.y};

    if(CheckCollisionCircleRec(other->base_t.pos.to_vec(),other->rad,my_rec)){
        if(!this->isStationary || !other->isStationary)
            return true;

        return true;
    }

    return return_value;
}

bool Core::BoxCollider2D::SolveCollision(Collider* other,f32 phy_delta){

    bool return_value = false;
    switch(other->getColliderType()){
        case Core::ColliderType::BOX_2D:
            SolveWithBoxCollider((Core::BoxCollider2D*)other,other->getId(),phy_delta);
            break;
        case Core::ColliderType::CIRCLE_2D:
            SolveWithCircleCollider((Core::CircleCollider2D*)other,other->getId(),phy_delta);
            break;
    }
    return return_value;
}
