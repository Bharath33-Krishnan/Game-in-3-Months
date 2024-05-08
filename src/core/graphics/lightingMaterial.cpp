#include "lightingMaterial.hpp"
#include "raylib/raylib.h"

void Core::LightingMaterial::initMaterial(vec3 ambientColor,Camera& mainCam){
    
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
    shader.locs[SHADER_LOC_MAP_SPECULAR] = GetShaderLocation(shader, "specularMap");

    int ambientLoc = GetShaderLocation(shader, "ambient");
    const float amibientArray[4] = {ambientColor.x,ambientColor.y,ambientColor.z,1.0};
    SetShaderValue(shader, ambientLoc, amibientArray, SHADER_UNIFORM_VEC4);
    this->ambientColor = ambientColor;
    this->mainCam = mainCam;

}

void Core::LightingMaterial::updateMaterial(){
    float cameraPos[3] = { mainCam.position.x, mainCam.position.y, mainCam.position.z };
    SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
    DrawLightGizmos();
}


void Core::LightingMaterial::DrawLightGizmos(){
    for (int i = 0; i < lightsCount; i++)
    {
        if (lights[i].enabled) DrawSphereEx(lights[i].position.to_vec(), 0.2f, 8, 8, lights[i].color);
        else DrawSphereWires(lights[i].position.to_vec(), 0.2f, 8, 8, ColorAlpha(lights[i].color, 0.3f));
    }
}

Core::Light Core::LightingMaterial::CreateLight(i32 type, vec3 position, vec3 target, Color color)
{
    Light light = { 0 };

    if (lightsCount < MAX_LIGHTS)
    {
        light.enabled = true;
        light.type = type;
        light.position = position;
        light.target = target;
        light.color = color;

        // NOTE: Lighting shader naming must be the provided ones
        light.enabledLoc = GetShaderLocation(shader, TextFormat("lights[%i].enabled", lightsCount));
        light.typeLoc = GetShaderLocation(shader, TextFormat("lights[%i].type", lightsCount));
        light.positionLoc = GetShaderLocation(shader, TextFormat("lights[%i].position", lightsCount));
        light.targetLoc = GetShaderLocation(shader, TextFormat("lights[%i].target", lightsCount));
        light.colorLoc = GetShaderLocation(shader, TextFormat("lights[%i].color", lightsCount));

        UpdateLightValues(light);
        
        TraceLog(LOG_INFO,TextFormat("Log %f %f %f"),light.position.x, light.position.y,light.position.z);
        lightsCount++;
    }

    lights.push_back(light);
    return light;
}

// Send light properties to shader
// NOTE: Light shader locations should be available 
void Core::LightingMaterial::UpdateLightValues(Light light)
{
    // Send to shader light enabled state and type
    SetShaderValue(shader, light.enabledLoc, &light.enabled, SHADER_UNIFORM_INT);
    SetShaderValue(shader, light.typeLoc, &light.type, SHADER_UNIFORM_INT);

    // Send to shader light position values
    float position[3] = { light.position.x, light.position.y, light.position.z };
    SetShaderValue(shader, light.positionLoc, position, SHADER_UNIFORM_VEC3);

    // Send to shader light target position values
    float target[3] = { light.target.x, light.target.y, light.target.z };
    SetShaderValue(shader, light.targetLoc, target, SHADER_UNIFORM_VEC3);

    // Send to shader light color values
    float color[4] = { (float)light.color.r/(float)255, (float)light.color.g/(float)255, 
                       (float)light.color.b/(float)255, (float)light.color.a/(float)255 };
    SetShaderValue(shader, light.colorLoc, color, SHADER_UNIFORM_VEC4);
}


