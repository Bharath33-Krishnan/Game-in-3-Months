#pragma once
#include "../core/drawable.hpp"
#include "raylib/raylib.h"
#include "sprite_manager.hpp"


class particle{
private:
    particle* NextParticle;
    SpriteSheet* sprite;
    transform t;

    u32 spriteFrame;
    i32 blendMode;

public:
    f32 rotSpeed;
    f32 scaleSpeed;
    vec2 vel;

    inline void initParticle(transform& t,SpriteSheet* sprite,u32 frame){
        this->sprite = sprite;
        this->spriteFrame = frame;
        this->t.pos = t.pos;
        this->t.rot = t.rot;
        this->t.scale = t.scale;
    }
    void update(f32 delta);
    inline void setNextParticle(particle* next){NextParticle = next;}
    inline particle* getNextParticle(){return NextParticle;}
    void draw();
};
