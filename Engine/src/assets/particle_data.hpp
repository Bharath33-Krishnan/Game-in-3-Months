#pragma once

#include "../utilities/data_types.hpp"
#include "sprite_manager.hpp"

struct particleEmitterData{
    vec2 angleRange;
    vec2 start_endSize;

    SpriteSheet tex;
    u32 texFrame;
    
    Color startColor;
    Color endColor;

    i32 blendMode;

    f32 emissionRate;
    f32 emissionVariance;
    f32 particle_lifetime;
    f32 speed;
    f32 rotSpeed;
};
