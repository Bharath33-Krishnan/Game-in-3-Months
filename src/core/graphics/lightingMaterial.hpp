#pragma once
#include "material.hpp"
#include <vector>

typedef enum {
    LIGHT_DIRECTIONAL = 0,
    LIGHT_POINT
} LightType;

#define MAX_LIGHTS  10         // Max dynamic lights supported by shader
namespace Core{



typedef struct {   
    int type;
    bool enabled;
    vec3 position;
    vec3 target;
    Color color;
    float attenuation;
    
    // Shader locations
    int enabledLoc;
    int typeLoc;
    int positionLoc;
    int targetLoc;
    int colorLoc;
    int attenuationLoc;
} Light;




class LightingMaterial:public EngineMaterial{
private:
    vec3 ambientColor;
    Camera mainCam;
    i32 lightsCount = 0;
    std::vector<Light> lights = std::vector<Light>(MAX_LIGHTS);
public:
    using EngineMaterial::EngineMaterial;
    void initMaterial(vec3 ambientColor,Camera& mainCam);
    void updateMaterial() override;
    Light CreateLight(i32 type, vec3 position, vec3 target, Color color);
    void UpdateLightValues(Light light);
    void DrawLightGizmos();
};
};
