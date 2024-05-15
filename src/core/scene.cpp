#include "scene.hpp"
#include "input.hpp"
#include <iostream>


Core::Scene::Scene() {
    entities = std::vector<Core::AbstractEntity*>(MAX_ENTITIES_PER_SCENE);
    loadThread = std::thread(&Core::Scene::loadResources,this);
    loading = true;
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
    DrawFPS(0, 0);

    // UpdateCamera(&camera, CAMERA_FIRST_PERSON);
    std::unordered_map<u8, std::vector<u16>>::iterator it;
    for (it = Core::InputHandler::KB_MOUSE_MAP.begin(); it != Core::InputHandler::KB_MOUSE_MAP.end(); it++) {
        bool event_occurred = Core::InputHandler::isEvent(it->first);

        // NOTE : Gowrish - uncomment to enable event debugging
        // if (event_occurred) {
        //     TraceLog(LOG_INFO, "[Inpute Handler] %s occurred", Core::InputHandler::EVENTS_NAME_MAP[it->first]);
        // }
    }
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
