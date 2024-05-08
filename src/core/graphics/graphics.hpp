#pragma once

#include "data_types.hpp"
#include "material.hpp"


//Note: Bharath -> Remove this LSP being Crazy
#include "raylib/raylib.h"

namespace Core{

#define MAX_MATERIALS_PER_SCENE 30

//Note : Bharath - This class handle contains all shaders and issues draw calls 
class GraphicsEngine{
private:
    std::vector<EngineMaterial*> materials;
    i32 registeredMaterialsNum = 0;
    f32 gammaCorrection = 2.2;

public:
    GraphicsEngine();
    ~GraphicsEngine();
    
    void RegisterMaterial(EngineMaterial* mat);
    void DrawEntites(vec3 camPos);
};

};

