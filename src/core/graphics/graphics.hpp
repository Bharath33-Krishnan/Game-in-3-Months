#pragma once

#include "data_types.hpp"
#include "material.hpp"


//Note: Bharath -> Remove this LSP being Crazy
#include "raylib/raylib.h"

namespace Core{

#define MAX_MATERIALS_PER_SCENE 30

class GraphicsEngine{
private:
    std::vector<EngineMaterial*> materials;

public:
    GraphicsEngine();
    ~GraphicsEngine();
    
    void RegisterMaterial(EngineMaterial* mat);
    void DrawEntites(vec3 camPos);
};

};

