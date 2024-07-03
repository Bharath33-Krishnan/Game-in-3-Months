#pragma once

#include "particle_data.hpp"
#include "../utilities/data_types.hpp"


class particle{
private:
    particle* NextParticle;
    transform t;
    vec2 vel;
    particleEmitterData* data;
    
    i32 framesAlive; 
    f32 lifeTime;
    bool alive = false;
    

public:
    void initParticle(vec2 pos,vec2 vel,particleEmitterData* data);
    void update(f32 delta);
    inline void setNextParticle(particle* next){NextParticle = next;}
    inline particle* getNextParticle(){return NextParticle;}
    bool isAlive();
    void draw();
};
