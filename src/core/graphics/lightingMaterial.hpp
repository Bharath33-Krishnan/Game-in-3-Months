#pragma once
#include "material.hpp"
#include <vector>

typedef enum {
    LIGHT_DIRECTIONAL = 0,
    LIGHT_POINT
} LightType;

#define MAX_LIGHTS  10         // Max dynamic lights supported by shader
namespace Core{

#define NUM_MAPS 3

enum class texture_types{
    TEXTURE_MAP_ALBEDO = 0,
    TEXTURE_MAP_NORMAL = 1,
    TEXTURE_MAP_SPECULAR = 2
};


typedef struct {   
    int type;
    bool enabled;
    Vector3 position;
    Vector3 target;
    Color color;
    Vector3 attenuation;
    
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
    f32 shine;
    Camera mainCam;
    i32 lightsCount = 0;
    std::vector<Light> lights = std::vector<Light>(MAX_LIGHTS);


    Texture2D* textures; 
public:
    using EngineMaterial::EngineMaterial;
    void initMaterial(vec3 ambientColor,float shine,Camera& mainCam);
    void addTexture(Texture2D& tex,texture_types loc);
    void updateMaterial() override;
    void setMaterial(Model model) override;
    Light CreateLight(i32 type,vec3 position,vec3 target,vec3 attenuation, Color color);
    void UpdateLightValues(Light light);
    void DrawLightGizmos();
};
};
