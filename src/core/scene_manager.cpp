#include "scene_manager.hpp"
#include "raylib/raylib.h"

std::vector<Core::Scene*> Core::SceneManager::scenes;
Core::Scene* Core::SceneManager::current_scene;

void Core::SceneManager::cleanUp() {
    for (Core::Scene* scene : scenes) {
        delete scene;
    }
}

void Core::SceneManager::addScene(Core::Scene* scene) {
    scenes.push_back(scene);
    current_scene = scene;
}

Core::Scene* Core::SceneManager::getCurrentScene() {
    return current_scene;
}

void Core::SceneManager::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(WHITE);
            current_scene->update(GetFrameTime());
            BeginMode3D(current_scene->getCamera());
                current_scene->draw();
                DrawGrid(10, 1.0f);
            EndMode3D();
        EndDrawing();
    }

    Core::SceneManager::cleanUp();
}