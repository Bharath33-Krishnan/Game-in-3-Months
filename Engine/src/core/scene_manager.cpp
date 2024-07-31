#include "scene_manager.hpp"
#include "raylib/raylib.h"
#include <string>

std::vector<Core::Scene*> Core::SceneManager::scenes;
Core::Scene* Core::SceneManager::current_scene = nullptr;

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

vec2 Core::SceneManager::getUpperLeftSceneCorner(){
    if(current_scene == nullptr)
        return  vec2(0);
    Camera2D& cam = current_scene->getCamera(); 
    return vec2(cam.target.x - GetScreenWidth()/2. , cam.target.y - GetScreenHeight()/2.);
}

void Core::SceneManager::run() {
    // current_scene->loadThread.join();

    while(!WindowShouldClose() && current_scene->loading){
        BeginDrawing();
            ClearBackground(WHITE);
            std::string loadStr= "Loading... Please don't close the window";
            int textSize = 20;
            DrawText(TextFormat("%s",loadStr.c_str()), (GetScreenWidth() - loadStr.length()*textSize)/2, GetScreenHeight()/2 , textSize, GREEN);
        EndDrawing();
    }
    current_scene->loadThread.join();
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(WHITE);
            current_scene->update(GetFrameTime());
            BeginMode2D(current_scene->getCamera());
                current_scene->draw();
            EndMode2D();
        EndDrawing();
    }

    Core::SceneManager::cleanUp();
}
