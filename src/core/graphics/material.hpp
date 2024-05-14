#pragma once
#include "data_types.hpp"
#include "../core/entity.hpp"
#include "raylib/raylib.h"
#include <vector>

#define MAX_ENTITIES_PER_MATERIAL 100


namespace Core{

//Note : Bharath - This class handle batching based on shaders
class EngineMaterial{
protected:
    Shader shader;
    i32 subscribedEntitiesNum = 0;
    std::vector<AbstractEntity*> subscribedEntities;


    bool loadedShader;
public:

    EngineMaterial(const char* vert_shader, const char* frag_shader){
        shader = LoadShader(vert_shader , frag_shader);
        loadedShader = true;
        subscribedEntities = std::vector<AbstractEntity*>(MAX_ENTITIES_PER_MATERIAL);
        LogInfoShader("Shader Loaded");
    }

    EngineMaterial(const Shader& shader){
        this->shader = shader;
        loadedShader = false;
        LogInfoShader("Shader Loaded");
    }


    ~EngineMaterial(){
        if(loadedShader)
        {
            LogInfoShader("Shader Unloaded");
            UnloadShader(shader);
            loadedShader = false;
        }
    }

    inline Shader getShader(){
        return shader;
    }


    inline std::vector<AbstractEntity*> getSubscribedEntities(){
        return subscribedEntities;
    }

    inline void LogInfoShader(){
        TraceLog(LOG_INFO,TextFormat("shader-> %d %d",shader.id)); 
    }

    inline void LogInfoShader(const char* text){
        TraceLog(LOG_INFO,TextFormat("%s %d",text,shader.id)); 
    }

    
    virtual void updateMaterial(){};

};

};


