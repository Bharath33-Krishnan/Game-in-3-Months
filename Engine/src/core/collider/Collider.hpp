#pragma once
#include "../../utilities/data_types.hpp"


namespace Core {

enum class ColliderType { BOX_2D, CIRCLE_2D };
enum class ColParams { POS, ROT, SCALE };

class Collider {
private:
    i32 Col_Id = -1;
    
protected:
    bool Collided = false;
    vec2 Offset = vec2(0,0);
    ColliderType collider_type;

public:
    bool isTrigger = false;
    bool isStationary = false;

    //********* Collission Solver **********
    virtual bool SolveCollision(Collider *other,f32 phy_delta = 1) = 0;// Particular Solver

    //********* Constructor***********
    Collider(){};

    //********* Getters ***********
    ColliderType getColliderType() { return collider_type; }
    virtual vec2 getParameter(ColParams param) = 0;
    inline i32 getId(){return Col_Id;}
    bool IsCollided() { return Collided; }
    bool getCachedData(Collider* other);

    //********* Setters ***********
    inline void setId(i32 id){Col_Id = id;}
    inline void setOffset(f32 Offset){this->Offset = Offset;}

    //********* Collision Interaction Funcs ***********
    inline bool onCollisionEnter(Collider *other) {
        if (!Collided)
            return (Collided = getCachedData(other)) == true;
        Collided = getCachedData(other);
        return false;
    }
    inline bool onCollisionStay(Collider *other) {
        return (Collided = getCachedData(other)) == true;
    }
    inline bool onCollisionExit(Collider *other) {
        if (Collided)
            return (Collided = getCachedData(other)) == false;
        Collided =  getCachedData(other);
        return false;
    }

    //********* Collider Debug Shapes ***********
    virtual void drawCollider() = 0;

    //********* Distructor ***********
    virtual ~Collider();
};

}; // namespace Core
