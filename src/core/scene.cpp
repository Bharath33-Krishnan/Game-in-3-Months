#include "scene.hpp"
#include "raylib/raylib.h"
#include <iostream>

Core::Scene::Scene() {
    entities = std::vector<Core::AbstractEntity*>(MAX_ENTITIES_PER_SCENE);
}

void Core::Scene::addEntity(Core::AbstractEntity* entity) {
    if (!entity) return;

    if (entityCounter >= MAX_ENTITIES_PER_SCENE) {
        std::cout << "Maximum number of entities reached" << std::endl;
        return;
    }
    entities[entityCounter++] = entity;
}

Core::Scene::~Scene() {
    for (Core::AbstractEntity* entity : entities) {
        delete entity;
    }
}

void Core::Scene::update(f32 delta) {
    UpdateCamera(&camera, CAMERA_FIRST_PERSON);
    for (Core::AbstractEntity* entity : entities) {
        // NOTE : Gowrish - Checking for NULLs since array is pre initialized
        if (entity) entity->update(delta);
    }
}

void Core::Scene::draw() {
    for (Core::AbstractEntity* entity : entities) {
        // NOTE : Gowrish - Checking for NULLs since array is pre initialized
        if (entity) entity->draw();
    }
}
