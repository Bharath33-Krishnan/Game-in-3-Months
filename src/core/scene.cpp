#include "scene.hpp"
#include "input.hpp"
#include "raylib/raylib.h"
#include <algorithm>
#include <iostream>
#include <vector>


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
    max_layer = std::max(max_layer,entity->getLayer());
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
    max_layer = 0;
    for (Core::AbstractEntity* entity : entities) {
        // NOTE : Gowrish - Checking for NULLs since array is pre initialized
        if (entity){
            entity->update(delta);
            max_layer = std::max(max_layer,entity->getLayer());
        }
    }
}


void drawNormal(Camera2D& mainCam,std::vector<Core::AbstractEntity*>& entities,u32 max_layer);
void drawChunk(Camera2D& mainCam,std::vector<Core::AbstractEntity*>& entities,u32 max_layer);

void Core::Scene::draw() {
    drawChunk(camera,entities,max_layer);
}

void drawNormal(Camera2D& mainCam,std::vector<Core::AbstractEntity*>& entities,u32 max_layer){
    for(u32 layer = 0; layer <= max_layer; layer++){
        for (Core::AbstractEntity* entity : entities) {
            // NOTE : Gowrish - Checking for NULLs since array is pre initialized
            if (entity){
                entity->draw(layer);
            }
        }
    }
}


bool isInsideChunk(vec2 Chunk,vec2 entityPos){

    return (entityPos.x < Chunk.x && entityPos.x >= Chunk.x - CHUNK_SIZE)  && (entityPos.y < Chunk.y && entityPos.y >= Chunk.y - CHUNK_SIZE);
}

void drawChunk(Camera2D& mainCam,std::vector<Core::AbstractEntity*>& entities,u32 max_layer){
    
    vec2 screenEdgeX = vec2(mainCam.target.x - GetRenderWidth()/2. , mainCam.target.x + GetRenderWidth()/2.);
    vec2 screenEdgeY = vec2(mainCam.target.y - GetRenderHeight()/2. , mainCam.target.y + GetRenderHeight()/2.);

    for(u32 layer = 0; layer <= max_layer; layer++){

        for(int XChunk = (int)screenEdgeX.x;XChunk <= ((int)screenEdgeX.y + 1 + CHUNK_SIZE) ; XChunk += CHUNK_SIZE){
            for(int YChunk = (int)screenEdgeY.x;YChunk <= ((int)screenEdgeY.y + 1 + CHUNK_SIZE) ; YChunk += CHUNK_SIZE){
                for (Core::AbstractEntity* entity : entities) {
                    // NOTE : Gowrish - Checking for NULLs since array is pre initialized
                    if (!entity)
                        continue;
                    if(!isInsideChunk(vec2(XChunk,YChunk), entity->getTransform().pos))
                        continue;
                    entity->draw(layer);
                }
            }

        }    
    }
    
    // TraceLog(LOG_INFO,"%f %f", mainCam.target.x, mainCam.target.y);
}
