#pragma once
#include "../core/drawable.hpp"
#include "raylib/raylib.h"
#include "sprite_manager.hpp"


class particle{
private:
    SpriteSheet sprite;
    transform t;
    u32 spriteFrame = 0;
    i32 blendMode;

public:
    virtual void ParticleBehaviour() = 0;
    
    void drawGfx() {
        BeginBlendMode(blendMode);
            sprite.DrawFrame(spriteFrame,t);
        EndBlendMode();
    }
};
