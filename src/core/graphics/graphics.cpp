#include "graphics.hpp"
#include "raylib/raylib.h"


Core::GraphicsEngine::GraphicsEngine(){
    materials = std::vector<EngineMaterial*>(MAX_MATERIALS_PER_SCENE);
}

Core::GraphicsEngine::~GraphicsEngine(){
    for(auto &material : materials){
        if(!material)
            break;
        delete material;
    }
}


void Core::GraphicsEngine::RegisterMaterial(Core::EngineMaterial* mat){
    if(registeredMaterialsNum >= MAX_MATERIALS_PER_SCENE){
        TraceLog(LOG_INFO,"Line %d Function %s File %s:  max materials size reacged",__LINE__,__FUNCTION__,__FILE__); 
        return;
    }
    SetShaderValue(mat->getShader(), GetShaderLocation(mat->getShader(), "gamma"), &gammaCorrection, SHADER_UNIFORM_FLOAT);
    materials[registeredMaterialsNum++] = mat;
}



void Core::GraphicsEngine::DrawEntites(vec3 camPos){
    for(auto material_instance: materials){
        if(material_instance){
            material_instance->updateMaterial();
            BeginShaderMode(material_instance->getShader());
                for(auto entity: material_instance->getSubscribedEntities()){
                    if (entity){ 
                        entity->draw();
                    }
                }
            EndShaderMode();
        }
    }
}


