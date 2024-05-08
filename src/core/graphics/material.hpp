#pragma once
#include "data_types.hpp"
#include "../core/entity.hpp"
#include "raylib/raylib.h"
#include <vector>

#define MAX_ENTITIES_PER_MATERIAL 100


namespace Core{

struct Engine_Texture2D{
    i32 type;
    Texture2D texture;
};

class EngineMaterial{
protected:
    Shader shader;
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
        }

    }

    inline void SubscribeToMaterial(AbstractEntity* entity){
        entity->setMaterial(this);
        subscribedEntities.push_back(entity);
    }

    // inline void AddTexture(Texture2D tex,i32 location){
    //     // material.maps[location].texture = tex;
    //     Engine_Texture2D m_tex = {0};
    //     m_tex.type = location;
    //     m_tex.texture = tex;
    //     textures.push_back(m_tex);
    // };

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


