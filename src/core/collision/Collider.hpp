#pragma once

namespace Core {

enum class ColliderType { BOX_2D , CIRCLE_2D };

class Collider {
private:
    bool Collided = false;

protected:
    ColliderType collider_type;
    //********* Virtual Functions ***********
    virtual bool SolveCollision(Collider& other)=0;

public:
    bool isTrigger = false;
    bool isCollidable = true;

    //********* Getters ***********
    Collider(){};

    //********* Getters ***********
    ColliderType getColliderType(){return collider_type;}
    bool IsCollided(){return Collided;}

    //********* Collision Interaction Funcs ***********
    inline bool onCollisionEnter(Collider& other){
        if(!Collided)
            return (Collided = SolveCollision(other)) == true;
        return false;
    }
    inline bool onCollisionStay(Collider& other){
        if(Collided)
            return (Collided = SolveCollision(other)) == true;
        return false;
    }
    inline bool onCollisionExit(Collider& other){
        if(Collided)
            return (Collided = SolveCollision(other)) == false;
        return false;
    }

    //********* Collider Debug Shapes ***********
    virtual void drawCollider() = 0;

    //********* Distructor ***********
    virtual ~Collider(){};
};

}; 

