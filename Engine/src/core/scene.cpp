#include "scene.hpp"
#include "PhysicsEngine.hpp"
#include "input.hpp"
#include <iostream>


Core::Scene::Scene() {
    entities = std::vector<Core::AbstractEntity*>(MAX_ENTITIES_PER_SCENE);
    loadThread = std::thread(&Core::Scene::loadResources,this);
    loading = true;

    max_layer = 0;
    entitiesPerLayer = std::vector<i32>(MAX_LAYER_POSSIBLE+1);
    for(i32 i = 0; i <= MAX_LAYER_POSSIBLE; i++){
        layerViseEntities.push_back(std::vector<Core::AbstractEntity*>(MAX_ENTITIES_PER_SCENE));
        entitiesPerLayer[i] = 0;
    }
}

void Core::Scene::addEntity(Core::AbstractEntity* entity) {
    if (!entity) return;

    if (entityCounter >= MAX_ENTITIES_PER_SCENE) {
        std::cout << "Maximum number of entities reached" << std::endl;
        return;
    }
    max_layer = std::max(max_layer,entity->getLayer());
    if(max_layer > MAX_LAYER_POSSIBLE)
        max_layer = MAX_LAYER_POSSIBLE;

    entities[entityCounter++] = entity;

}

Core::Scene::~Scene() {
    for (Core::AbstractEntity* entity : entities) {
        delete entity;
    }
}

void Core::Scene::update(f32 delta) {
    DrawFPS(0, 0);

    // NOTE: Bharath: Physics Update Code Gonna Go Here

    for(int i = 0 ; i < PHYSICS_CLOCK_PER_FRAME;i++){
        PhysicsEngine::GenerateSpatialGrid();
        PhysicsEngine::SolveCollissions(delta/PHYSICS_CLOCK_PER_FRAME);
    }

    // NOTE: Bharath: End of Physics Update

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
            if(max_layer > MAX_LAYER_POSSIBLE)
                max_layer = MAX_LAYER_POSSIBLE;
        }
    }
    for(i32 i = 0; i <= MAX_LAYER_POSSIBLE; i++){
        entitiesPerLayer[i] = 0;
    }
}



void Core::Scene::draw() {
    drawChunk();
}

void Core::Scene::drawNormal(){
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

void Core::Scene::drawChunk(){
    
    vec2 screenEdgeX = vec2(camera.target.x - GetRenderWidth()/2. , camera.target.x + GetRenderWidth()/2.);
    vec2 screenEdgeY = vec2(camera.target.y - GetRenderHeight()/2. , camera.target.y + GetRenderHeight()/2.);

        for(int YChunk = (int)screenEdgeY.x;YChunk <= ((int)screenEdgeY.y + 1 +  EXTRA_CHUNKS * CHUNK_SIZE) ; YChunk += CHUNK_SIZE){
            for(int XChunk = (int)screenEdgeX.x;XChunk <= ((int)screenEdgeX.y + 1 + EXTRA_CHUNKS * CHUNK_SIZE) ; XChunk += CHUNK_SIZE){
                for (Core::AbstractEntity* entity : entities) {
                    // NOTE : Gowrish - Checking for NULLs since array is pre initialized
                    if (!entity)
                        continue;
                    if(!isInsideChunk(vec2(XChunk,YChunk), entity->getTransform().pos))
                        continue;
                    // TraceLog(LOG_INFO, "%d %d",XChunk,YChunk); 
                    layerViseEntities[entity->getLayer()][entitiesPerLayer[entity->getLayer()]++] = entity;
                    // entitiesPerLayer[entity->getLayer()]++;
                    // entity->draw(layer);
                }
            }
        }    

    for(u32 layer = 0; layer <= max_layer; layer++){
        for(i32 i = 0 ; i < entitiesPerLayer[layer];i++){
            layerViseEntities[layer][i]->draw(layer);
        }
    }
    
    // TraceLog(LOG_INFO,"%f %f", mainCam.target.x, mainCam.target.y);
}
