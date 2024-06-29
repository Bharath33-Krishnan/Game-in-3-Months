#include "BoxCollider2D.hpp"
#include "raylib/raylib.h"
#include <algorithm>

bool Core::BoxCollider2D::SolveWithBoxCollider(Core::BoxCollider2D* other,int id){
    Rectangle my_rec = {base_t.pos.x,base_t.pos.y,diagonal.x,diagonal.y};
    Rectangle other_rec = {other->base_t.pos.x,other->base_t.pos.y,other->diagonal.x,other->diagonal.y};

    if(CheckCollisionRecs(my_rec, other_rec)){
        if(!this->isCollidable || !other->isCollidable)
            return true;
        Rectangle overlap_rec = GetCollisionRec(my_rec, other_rec);
        float sep =  0.1 * std::max(overlap_rec.width,overlap_rec.height);
        vec2 sep_vec = sep * (this->base_t.pos - other->base_t.pos).normalize();
        other->base_t.pos = other->base_t.pos - sep_vec;
        this->base_t.pos = this->base_t.pos + sep_vec;
        return true;
    }
    return false;
}


bool Core::BoxCollider2D::SolveWithCircleCollider(Core::CircleCollider2D* other,int id){
    bool return_value = false;
    Rectangle my_rec = {base_t.pos.x,base_t.pos.y,diagonal.x,diagonal.y};

    if(CheckCollisionCircleRec(other->base_t.pos.to_vec(),other->rad,my_rec)){
        if(!this->isCollidable || !other->isCollidable)
            return true;

        return true;
    }

    return return_value;
}

bool Core::BoxCollider2D::SolveCollision(Collider* other){

    bool return_value = false;
    switch(other->getColliderType()){
        case Core::ColliderType::BOX_2D:
            SolveWithBoxCollider((Core::BoxCollider2D*)other,other->getId());
            break;
        case Core::ColliderType::CIRCLE_2D:
            SolveWithCircleCollider((Core::CircleCollider2D*)other,other->getId());
            break;
    }
    return return_value;
}
