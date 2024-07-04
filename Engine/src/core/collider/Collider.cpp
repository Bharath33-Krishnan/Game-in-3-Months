#include "../PhysicsEngine.hpp"

bool Core::Collider::getCachedData(Collider* other){
    return PhysicsEngine::GetCachedCollissionData(this, other);
}

Core::Collider::~Collider(){
    if(Col_Id < 0)
        return;

    PhysicsEngine::getColliders()[Col_Id] = nullptr;
}
