#include "../PhysicsEngine.hpp"


Core::Collider::~Collider(){
    if(Col_Id < 0)
        return;

    PhysicsEngine::getColliders()[Col_Id] = nullptr;
}
