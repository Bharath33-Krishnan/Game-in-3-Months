#pragma once
#include <vector>
#include "collision/Core_Colliders.hpp"

#define MAX_COLLIDERS 1000
namespace Core{
/*
 * NOTE: : Physics Engine Does Not Manage Colliders,
 * its destruction and initialisation should be managed by the programmer
 * Its just a container for quick access for collission calculations
*/
class PhysicsEngine{

private:
    //************ Properties ************
    static int num_colliders;
    static std::vector<Collider*> colliders;

public:
    //************ Functions ************
    static void registerCollider(Collider* col);
    static std::vector<Collider*> getColliders();
};

};
