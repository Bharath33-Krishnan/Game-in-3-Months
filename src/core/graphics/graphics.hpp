#pragma once

#include "data_types.hpp"
#include "material.hpp"

namespace Core{

#define MAX_MATERIALS_PER_SCENE 30

//Note : Bharath - This class handle contains all shaders and issues draw calls 
class GraphicsEngine{
private:
    static std::vector<EngineMaterial*> materials; 
    static i32 registeredMaterialsNum;
    static f32 gammaCorrection;

public:
    // GraphicsEngine();
    // ~GraphicsEngine();
    
    static void InitialiseEngine(f32 gammaCorrection);
    static void RegisterMaterial(EngineMaterial* mat);
    static void DrawEntites(vec3 camPos);
    static void DestroyMaterials();
};

};

