#include "PhysicsEngine.hpp"

std::vector<Core::Collider*> Core::PhysicsEngine::colliders(MAX_COLLIDERS);
int Core::PhysicsEngine::num_colliders = 0;

void Core::PhysicsEngine::registerCollider(Collider *col){
   colliders[num_colliders++] = col;
}

std::vector<Core::Collider*> Core::PhysicsEngine::getColliders(){
    return colliders;
}
