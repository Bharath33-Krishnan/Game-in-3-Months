#pragma once
#include "data_types.hpp"
#include "particle.hpp"


struct particleEmitterData{
    vec2 angleRange;
    vec2 start_endSize;
    
    f32 emissionRate;
    f32 emissionVariance;
    f32 particle_lifetime;
    f32 speed;
    f32 rotSpeed;
};

class ParticleEmitter{
private:
    particleEmitterData data;
    particle* particlePool;
    i32 particlePoolSize;

public:
    ParticleEmitter(particleEmitterData data);
    void updateData(particleEmitterData data){this->data = data;};
    inline particleEmitterData getData(){return data;};
    ~ParticleEmitter();
};
