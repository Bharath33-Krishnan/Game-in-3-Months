#pragma once
#include "scene.hpp"

namespace Core {

class SceneManager {
public:
    static std::vector<Core::Scene*> scenes;
    static Core::Scene* current_scene; 

    static void addScene(Core::Scene* scene);
    static Core::Scene* getCurrentScene();
    static vec2 getUpperLeftSceneCorner();
    static void run();
    static void cleanUp();
};
}
