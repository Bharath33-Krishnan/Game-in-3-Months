#pragma once

#include <vector>
#include "entity.hpp"
#include "graphics/graphics.hpp"

#define MAX_ENTITIES_PER_SCENE 100

namespace Core {

class Scene {
private:
    std::vector<Core::AbstractEntity*> entities;
    Camera camera;
    i32 entityCounter = 0;
public:
    Scene();

    void addEntity(Core::AbstractEntity* entity);
    virtual void update(f32 delta);
    virtual void draw();
    inline i32 getEntitiesCount() { return entityCounter; }
    inline Camera& getCamera() { return camera; }
    inline void setCamera(Camera cam) { camera = cam; }

    ~Scene();
};

}
